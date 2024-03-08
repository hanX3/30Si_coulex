#include "PhysicsList.hh"

//
PhysicsList::PhysicsList(Projectile *p, Recoil *r, DetectorConstruction *dc)
: projectile(p),
  recoil(r),
  detector_construction(dc)
{
  step_size = 0.05 *um;
  custom_stopping = false;
  reaction_type = -1;
}

//
PhysicsList::~PhysicsList()
{

}

//
void PhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program.

  G4BosonConstructor bs_constructor;
  bs_constructor.ConstructParticle();
  G4LeptonConstructor l_constructor;
  l_constructor.ConstructParticle();
  G4MesonConstructor m_constructor;
  m_constructor.ConstructParticle();
  G4BaryonConstructor br_constructor;
  br_constructor.ConstructParticle();

  //  ions
  G4IonConstructor i_constructor;
  i_constructor.ConstructParticle();
}

//
void PhysicsList::ConstructProcess()
{
  // Define transportation process

  AddTransportation();
  ConstructEM();
}

//
void PhysicsList::ConstructEM()
{
  G4cout << "Setting up physics..." << G4endl;
  G4cout << "Step size: " << step_size/um << " um" << G4endl;
  
  if(custom_stopping){
    G4cout << "Will use custom GenericIon stopping power tables from directory: " << cs_path << G4endl;
  }else{
    G4cout << "Will use default GenericIon stopping power tables." << G4endl;
  }

  GetParticleIterator()->reset();

  while((*GetParticleIterator())()) {
    G4ParticleDefinition *particle = GetParticleIterator()->value();
    G4ProcessManager *p_manager = particle->GetProcessManager();
    G4String particle_name = particle->GetParticleName();

    // G4cout << "++++ Particle name = " << particle_name << G4endl;

    if(particle_name == "gamma"){
      p_manager->AddDiscreteProcess(new G4PhotoElectricEffect());
      p_manager->AddDiscreteProcess(new G4ComptonScattering());
      p_manager->AddDiscreteProcess(new G4GammaConversion());
    }else if(particle_name == "e-"){
      p_manager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      p_manager->AddProcess(new G4eIonisation, -1, 2, 2);
      p_manager->AddProcess(new G4eBremsstrahlung, -1, 3, 3);
    }else if(particle_name == "e+"){
      p_manager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      p_manager->AddProcess(new G4eIonisation, -1, 2, 2);
      p_manager->AddProcess(new G4eBremsstrahlung, -1, 3, 3);
      p_manager->AddProcess(new G4eplusAnnihilation, 0, -1, 4);
    }else if(particle_name == "proton"){
      p_manager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      G4hIonisation *proton_ioni = new G4hIonisation(); 
      proton_ioni->SetStepFunction(0.05, 0.05 *um); 
      p_manager->AddProcess(proton_ioni, -1, 2, 2);
    }else if(particle_name == "alpha"){
      p_manager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      G4ionIonisation *alpha_ioni = new G4ionIonisation();
      alpha_ioni->SetStepFunction(0.05, 0.05 * um);
      p_manager->AddProcess(alpha_ioni, -1, 2, 2);
      
      // small for light particles
      // p_manager->AddProcess(new G4NuclearStopping(), -1, 3, -1);
      
      // what does this do?
      p_manager->AddProcess(new G4StepLimiter, -1, -1, 4);
    }else if(particle_name == "GenericIon"){
      p_manager->AddProcess(new G4hMultipleScattering, -1, 1, 1);

      /*
      //Added by JW
      G4ScreenedNuclearRecoil *nucr = new G4ScreenedNuclearRecoil();
      G4double energy_limit = 100.*GeV;
      nucr->SetMaxEnergyForScattering(energy_limit);
      p_manager->AddDiscreteProcess(nucr);
      */

      /*
      //Added by JW
      G4CoulombScattering *cs = new G4CoulombScattering();
      cs->AddEmModel(0, new G4IonCoulombScatteringModel());
      pmanager->AddDiscreteProcess(cs);
      */

      G4ionIonisation *ion_ioni = new G4ionIonisation();
      
      // ICRU 73 based model, valid for Z = 3 to 26, modified by JW to allow for custom stopping powers
      G4IonParametrisedLossModel *the_model = new G4IonParametrisedLossModel();
      if(custom_stopping){
        G4IonStoppingData *isd = new G4IonStoppingData(cs_path);
        for(int z1=1;z1<100;z1++){
          for(int z2=1;z2<100;z2++){
            isd->BuildPhysicsVector(z1, z2);
          }
        }

        // add stopping power data from data files
        the_model->RemoveDEDXTable("ICRU73");
        the_model->AddDEDXTable("Custom", isd, new G4IonDEDXScalingICRU73());
        if(isd->CheckEmpty()){
          G4cout << "ERROR: Ion stopping data is empty!" << G4endl;
          G4cout << "Are you using custom stopping tables with the wrong path ?" << G4endl;
          exit(-1);
        }
        isd->DumpMap();
      }

      the_model->ListDEDXTables();
      // the_model->PrintDEDXTable(theProjectile,const G4Material *,0.1,10.0,20,false);
      // small step size needed for short lifetimes ?
      ion_ioni->SetStepFunction(0.05, step_size);
      ion_ioni->SetEmModel(the_model);
      p_manager->AddProcess(ion_ioni, -1, 3, 2);
      p_manager->AddProcess(new G4NuclearStopping(), -1, 4, -1);
      switch(reaction_type){
        case 0:
          // coulex
          reaction_coulex = new ReactionCoulex(projectile, recoil);
          p_manager->AddProcess(reaction_coulex, -1, -1, 3);
          break;
        default:
          G4cout << "ERROR: no reaction mechanism specified." << G4endl;
          exit(-1);
      }
      p_manager->AddProcess(new G4StepLimiter, -1, -1, 4);
    }else if(particle_name == "neutron"){
      if (use_neutrons) {
        // elastic scattering
        // This scheme copied from geant4 application developer guide sec 5.2.2.4.
        // Old scheme from geant4.9.4 which doesn't compile anymore was commented out.
        G4HadronElasticProcess *the_elastic_process = new G4HadronElasticProcess;
        // Cross Section Data set
        G4NeutronHPElasticData *the_HP_elastic_data = new G4NeutronHPElasticData;
        the_elastic_process->AddDataSet(the_HP_elastic_data);
        G4NeutronHPThermalScatteringData *the_HP_thermal_scattering_data = new G4NeutronHPThermalScatteringData;
        the_elastic_process->AddDataSet(the_HP_thermal_scattering_data);
        // Models
        G4NeutronHPElastic *the_elastic_model = new G4NeutronHPElastic;
        the_elastic_model->SetMinEnergy(4.0 *eV);
        the_elastic_process->RegisterMe(the_elastic_model);
        G4NeutronHPThermalScattering *the_neutron_thermal_elastic_model = new G4NeutronHPThermalScattering;
        the_neutron_thermal_elastic_model->SetMaxEnergy(4.0 *eV);
        the_elastic_process->RegisterMe(the_neutron_thermal_elastic_model);

        /*
        G4HadronElasticProcess* the_elastic_process = new G4HadronElasticProcess();
        G4LElastic* the_elastic_model = new G4LElastic;
        the_elastic_process->RegisterMe(the_elastic_model);
        */
        p_manager->AddDiscreteProcess(the_elastic_process);

        // inelastic scattering
        G4HadronInelasticProcess *the_inelastic_process = new G4HadronInelasticProcess("inelastic");
        // new for geant4.10.1
        G4NeutronHPInelastic *the_inelastic_model = new G4NeutronHPInelastic;
        // for geant4.9.4
        // G4LENeutronInelastic *the_inelastic_model = new G4LENeutronInelastic;
        the_inelastic_process->RegisterMe(the_inelastic_model);
        p_manager->AddDiscreteProcess(the_inelastic_process);
        // fission
        G4NeutronFissionProcess *the_fission_process = new G4NeutronFissionProcess;
        G4LFission *the_fission_model = new G4LFission;
        the_fission_process->RegisterMe(the_fission_model);
        p_manager->AddDiscreteProcess(the_fission_process);
        // capture
        G4NeutronCaptureProcess *the_capture_process = new G4NeutronCaptureProcess;
        // new for geant4.10.1
        G4NeutronHPCapture *the_capture_model = new G4NeutronHPCapture;
        // for geant4.9.4
        // G4LCapture* the_capture_model = new G4LCapture;
        the_capture_process->RegisterMe(the_capture_model);
        p_manager->AddDiscreteProcess(the_capture_process);
      }else{
        G4cout << "Neutron interactions are not used in this simulation." << G4endl;
      }
    }
  }
}

