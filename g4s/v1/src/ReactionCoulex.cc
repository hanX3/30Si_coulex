#include "ReactionCoulex.hh"

//  
ReactionCoulex::ReactionCoulex(Projectile *p, Recoil *r, const G4String &process_name)
: G4VProcess(process_name), theRecoil(r),theProjectile(p)
{
  reaction_here = false;

  //
  v_ksi_array.push_back(0.);
  v_ksi_array.push_back(0.1);
  v_ksi_array.push_back(0.2);
  v_ksi_array.push_back(0.3);
  v_ksi_array.push_back(0.4);
  v_ksi_array.push_back(0.5);
  v_ksi_array.push_back(0.6);
  v_ksi_array.push_back(0.7);
  v_ksi_array.push_back(0.8);
  v_ksi_array.push_back(0.9);
  v_ksi_array.push_back(1.);
  v_ksi_array.push_back(1.2);
  v_ksi_array.push_back(1.4);
  v_ksi_array.push_back(1.6);
  v_ksi_array.push_back(1.8);
  v_ksi_array.push_back(2.);
  v_ksi_array.push_back(4.);

  //
  v_fksi_array.push_back(0.895);
  v_fksi_array.push_back(0.859);
  v_fksi_array.push_back(0.729);
  v_fksi_array.push_back(0.561);
  v_fksi_array.push_back(0.4046);
  v_fksi_array.push_back(0.2781);
  v_fksi_array.push_back(0.1844);
  v_fksi_array.push_back(0.1189);
  v_fksi_array.push_back(7.510E-02);
  v_fksi_array.push_back(4.663E-02);
  v_fksi_array.push_back(2.855E-02);
  v_fksi_array.push_back(1.035E-02);
  v_fksi_array.push_back(3.628E-03);
  v_fksi_array.push_back(1.238E-03);
  v_fksi_array.push_back(4.143E-04);
  v_fksi_array.push_back(1.363E-04);
  v_fksi_array.push_back(1.247E-09);

  //
  v_theta_array.push_back(0.);
  v_theta_array.push_back(10.);
  v_theta_array.push_back(20.);
  v_theta_array.push_back(30.);
  v_theta_array.push_back(40.);
  v_theta_array.push_back(50.);
  v_theta_array.push_back(60.);
  v_theta_array.push_back(70.);
  v_theta_array.push_back(80.);
  v_theta_array.push_back(90.);
  v_theta_array.push_back(100.);
  v_theta_array.push_back(110.);
  v_theta_array.push_back(120.);
  v_theta_array.push_back(130.);
  v_theta_array.push_back(140.);
  v_theta_array.push_back(150.);
  v_theta_array.push_back(160.);
  v_theta_array.push_back(170.);
  v_theta_array.push_back(180.);

  v_th000.push_back(1.676E-01);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);
  v_th000.push_back(0.000E+00);

  v_th010.push_back(1.385E-01);
  v_th010.push_back(1.403E-01);
  v_th010.push_back(5.210E-02);
  v_th010.push_back(1.110E-02);
  v_th010.push_back(1.788E-03);
  v_th010.push_back(2.443E-04);
  v_th010.push_back(2.996E-05);
  v_th010.push_back(3.403E-06);
  v_th010.push_back(3.652E-07);
  v_th010.push_back(3.750E-08);
  v_th010.push_back(3.719E-09);
  v_th010.push_back(3.374E-11);
  v_th010.push_back(2.824E-13);
  v_th010.push_back(2.227E-15);
  v_th010.push_back(1.679E-17);
  v_th010.push_back(1.220E-19);
  v_th010.push_back(1.750E-41);

  v_th020.push_back(1.178E-01);
  v_th020.push_back(1.286E-01);
  v_th020.push_back(1.016E-01);
  v_th020.push_back(5.780E-02);
  v_th020.push_back(2.678E-02);
  v_th020.push_back(1.085E-02);
  v_th020.push_back(4.005E-03);
  v_th020.push_back(1.382E-03);
  v_th020.push_back(4.531E-04);
  v_th020.push_back(1.427E-04);
  v_th020.push_back(4.351E-05);
  v_th020.push_back(3.752E-06);
  v_th020.push_back(2.998E-07);
  v_th020.push_back(2.265E-08);
  v_th020.push_back(1.638E-09);
  v_th020.push_back(1.144E-10);
  v_th020.push_back(1.134E-22);

  v_th030.push_back(1.027E-01);
  v_th030.push_back(1.087E-01);
  v_th030.push_back(9.810E-02);
  v_th030.push_back(7.160E-02);
  v_th030.push_back(4.474E-02);
  v_th030.push_back(2.508E-02);
  v_th030.push_back(1.300E-02);
  v_th030.push_back(6.350E-03);
  v_th030.push_back(2.960E-03);
  v_th030.push_back(1.331E-03);
  v_th030.push_back(5.810E-04);
  v_th030.push_back(1.032E-04);
  v_th030.push_back(1.708E-05);
  v_th030.push_back(2.680E-06);
  v_th030.push_back(4.032E-07);
  v_th030.push_back(5.870E-08);
  v_th030.push_back(0.929E-16);

  v_th040.push_back(9.160E-02);
  v_th040.push_back(9.430E-02);
  v_th040.push_back(8.730E-02);
  v_th040.push_back(6.940E-02);
  v_th040.push_back(4.895E-02);
  v_th040.push_back(3.154E-02);
  v_th040.push_back(1.899E-02);
  v_th040.push_back(1.085E-02);
  v_th040.push_back(5.950E-03);
  v_th040.push_back(3.159E-03);
  v_th040.push_back(1.631E-03);
  v_th040.push_back(4.076E-04);
  v_th040.push_back(9.530E-05);
  v_th040.push_back(2.118E-05);
  v_th040.push_back(4.523E-06);
  v_th040.push_back(9.360E-07);
  v_th040.push_back(0.518E-13);

  v_th050.push_back(8.320E-02);
  v_th050.push_back(8.370E-02);
  v_th050.push_back(7.720E-02);
  v_th050.push_back(6.340E-02);
  v_th050.push_back(4.715E-02);
  v_th050.push_back(3.251E-02);
  v_th050.push_back(2.113E-02);
  v_th050.push_back(1.311E-02);
  v_th050.push_back(7.840E-03);
  v_th050.push_back(4.553E-03);
  v_th050.push_back(2.577E-03);
  v_th050.push_back(7.770E-04);
  v_th050.push_back(2.203E-04);
  v_th050.push_back(5.950E-05);
  v_th050.push_back(1.549E-05);
  v_th050.push_back(3.913E-06);
  v_th050.push_back(1.643E-12);

  v_th060.push_back(7.680E-02);
  v_th060.push_back(7.580E-02);
  v_th060.push_back(6.900E-02);
  v_th060.push_back(5.700E-02);
  v_th060.push_back(4.341E-02);
  v_th060.push_back(3.095E-02);
  v_th060.push_back(2.095E-02);
  v_th060.push_back(1.361E-02);
  v_th060.push_back(8.550E-03);
  v_th060.push_back(5.230E-03);
  v_th060.push_back(3.123E-03);
  v_th060.push_back(1.054E-03);
  v_th060.push_back(3.356E-04);
  v_th060.push_back(1.022E-04);
  v_th060.push_back(3.001E-05);
  v_th060.push_back(8.570E-06);
  v_th060.push_back(1.269E-11);

  v_th070.push_back(7.190E-02);
  v_th070.push_back(6.970E-02);
  v_th070.push_back(6.240E-02);
  v_th070.push_back(5.130E-02);
  v_th070.push_back(3.932E-02);
  v_th070.push_back(2.846E-02);
  v_th070.push_back(1.967E-02);
  v_th070.push_back(1.311E-02);
  v_th070.push_back(8.470E-03);
  v_th070.push_back(5.340E-03);
  v_th070.push_back(3.294E-03);
  v_th070.push_back(1.191E-03);
  v_th070.push_back(4.079E-04);
  v_th070.push_back(1.339E-04);
  v_th070.push_back(4.249E-05);
  v_th070.push_back(1.312E-05);
  v_th070.push_back(4.434E-11);

  v_th080.push_back(6.800E-02);
  v_th080.push_back(6.490E-02);
  v_th080.push_back(5.700E-02);
  v_th080.push_back(4.643E-02);
  v_th080.push_back(3.549E-02);
  v_th080.push_back(2.579E-02);
  v_th080.push_back(1.798E-02);
  v_th080.push_back(1.213E-02);
  v_th080.push_back(7.960E-03);
  v_th080.push_back(5.100E-03);
  v_th080.push_back(3.211E-03);
  v_th080.push_back(1.211E-03);
  v_th080.push_back(4.338E-04);
  v_th080.push_back(1.494E-04);
  v_th080.push_back(4.985E-05);
  v_th080.push_back(1.621E-05);
  v_th080.push_back(0.950E-10);

  v_th090.push_back(6.500E-02);
  v_th090.push_back(6.120E-02);
  v_th090.push_back(5.270E-02);
  v_th090.push_back(4.234E-02);
  v_th090.push_back(3.210E-02);
  v_th090.push_back(2.326E-02);
  v_th090.push_back(1.624E-02);
  v_th090.push_back(1.100E-02);
  v_th090.push_back(7.270E-03);
  v_th090.push_back(4.700E-03);
  v_th090.push_back(2.986E-03);
  v_th090.push_back(1.153E-03);
  v_th090.push_back(4.245E-04);
  v_th090.push_back(1.506E-04);
  v_th090.push_back(5.190E-05);
  v_th090.push_back(1.743E-05);
  v_th090.push_back(1.477E-10);

  v_th100.push_back(6.270E-02);
  v_th100.push_back(5.830E-02);
  v_th100.push_back(4.930E-02);
  v_th100.push_back(3.895E-02);
  v_th100.push_back(2.920E-02);
  v_th100.push_back(2.100E-02);
  v_th100.push_back(1.460E-02);
  v_th100.push_back(9.880E-03);
  v_th100.push_back(6.530E-03);
  v_th100.push_back(4.232E-03);
  v_th100.push_back(2.699E-03);
  v_th100.push_back(1.054E-03);
  v_th100.push_back(3.936E-04);
  v_th100.push_back(1.420E-04);
  v_th100.push_back(4.983E-05);
  v_th100.push_back(1.708E-05);
  v_th100.push_back(1.842E-10);

  v_th110.push_back(6.080E-02);
  v_th110.push_back(5.590E-02);
  v_th110.push_back(4.651E-02);
  v_th110.push_back(3.617E-02);
  v_th110.push_back(2.676E-02);
  v_th110.push_back(1.905E-02);
  v_th110.push_back(1.314E-02);
  v_th110.push_back(8.840E-03);
  v_th110.push_back(5.820E-03);
  v_th110.push_back(3.769E-03);
  v_th110.push_back(2.402E-03);
  v_th110.push_back(9.390E-04);
  v_th110.push_back(3.526E-04);
  v_th110.push_back(1.282E-04);
  v_th110.push_back(4.538E-05);
  v_th110.push_back(1.572E-05);
  v_th110.push_back(1.964E-10);

  v_th120.push_back(5.930E-02);
  v_th120.push_back(5.410E-02);
  v_th120.push_back(4.428E-02);
  v_th120.push_back(3.391E-02);
  v_th120.push_back(2.475E-02);
  v_th120.push_back(1.741E-02);
  v_th120.push_back(1.190E-02);
  v_th120.push_back(7.940E-03);
  v_th120.push_back(5.200E-03);
  v_th120.push_back(3.345E-03);
  v_th120.push_back(2.123E-03);
  v_th120.push_back(8.260E-04);
  v_th120.push_back(3.904E-04);
  v_th120.push_back(1.125E-04);
  v_th120.push_back(3.990E-05);
  v_th120.push_back(1.387E-05);
  v_th120.push_back(1.869E-10);

  v_th130.push_back(5.820E-02);
  v_th130.push_back(5.260E-02);
  v_th130.push_back(4.252E-02);
  v_th130.push_back(3.210E-02);
  v_th130.push_back(2.311E-02);
  v_th130.push_back(1.606E-02);
  v_th130.push_back(1.086E-02);
  v_th130.push_back(7.180E-03);
  v_th130.push_back(4.660E-03);
  v_th130.push_back(2.979E-03);
  v_th130.push_back(1.879E-03);
  v_th130.push_back(7.240E-04);
  v_th130.push_back(2.691E-04);
  v_th130.push_back(9.730E-05);
  v_th130.push_back(3.439E-05);
  v_th130.push_back(1.193E-05);
  v_th130.push_back(1.640E-10);

  v_th140.push_back(5.730E-02);
  v_th140.push_back(5.150E-02);
  v_th140.push_back(4.115E-02);
  v_th140.push_back(3.068E-02);
  v_th140.push_back(2.182E-02);
  v_th140.push_back(1.499E-02);
  v_th140.push_back(1.003E-02);
  v_th140.push_back(6.570E-03);
  v_th140.push_back(4.224E-03);
  v_th140.push_back(2.678E-03);
  v_th140.push_back(1.677E-03);
  v_th140.push_back(6.370E-04);
  v_th140.push_back(2.344E-04);
  v_th140.push_back(8.400E-05);
  v_th140.push_back(2.947E-05);
  v_th140.push_back(1.016E-05);
  v_th140.push_back(1.364E-10);

  v_th150.push_back(5.660E-02);
  v_th150.push_back(5.070E-02);
  v_th150.push_back(4.013E-02);
  v_th150.push_back(2.961E-02);
  v_th150.push_back(2.085E-02);
  v_th150.push_back(1.418E-02);
  v_th150.push_back(9.390E-03);
  v_th150.push_back(6.090E-03);
  v_th150.push_back(3.888E-03);
  v_th150.push_back(2.445E-03);
  v_th150.push_back(1.519E-03);
  v_th150.push_back(5.690E-04);
  v_th150.push_back(2.069E-04);
  v_th150.push_back(7.330E-05);
  v_th150.push_back(2.546E-05);
  v_th150.push_back(8.700E-06);
  v_th150.push_back(1.106E-10);

  v_th160.push_back(5.620E-02);
  v_th160.push_back(5.010E-02);
  v_th160.push_back(3.942E-02);
  v_th160.push_back(2.887E-02);
  v_th160.push_back(2.017E-02);
  v_th160.push_back(1.361E-02);
  v_th160.push_back(8.950E-03);
  v_th160.push_back(5.760E-03);
  v_th160.push_back(3.650E-03);
  v_th160.push_back(2.280E-03);
  v_th160.push_back(1.407E-03);
  v_th160.push_back(5.210E-04);
  v_th160.push_back(1.870E-04);
  v_th160.push_back(6.560E-05);
  v_th160.push_back(2.254E-05);
  v_th160.push_back(7.630E-06);
  v_th160.push_back(0.904E-10);

  v_th170.push_back(5.590E-02);
  v_th170.push_back(4.980E-02);
  v_th170.push_back(3.900E-02);
  v_th170.push_back(2.844E-02);
  v_th170.push_back(1.977E-02);
  v_th170.push_back(1.328E-02);
  v_th170.push_back(8.690E-03);
  v_th170.push_back(5.570E-03);
  v_th170.push_back(3.509E-03);
  v_th170.push_back(2.181E-03);
  v_th170.push_back(1.340E-03);
  v_th170.push_back(4.918E-04);
  v_th170.push_back(1.751E-04);
  v_th170.push_back(6.090E-05);
  v_th170.push_back(2.078E-05);
  v_th170.push_back(6.980E-06);
  v_th170.push_back(0.779E-10);

  v_th180.push_back(5.580E-02);
  v_th180.push_back(4.969E-02);
  v_th180.push_back(3.887E-02);
  v_th180.push_back(2.829E-02);
  v_th180.push_back(1.963E-02);
  v_th180.push_back(1.316E-02);
  v_th180.push_back(8.600E-03);
  v_th180.push_back(5.500E-03);
  v_th180.push_back(3.462E-03);
  v_th180.push_back(2.148E-03);
  v_th180.push_back(1.318E-03);
  v_th180.push_back(4.822E-04);
  v_th180.push_back(1.712E-04);
  v_th180.push_back(5.930E-05);
  v_th180.push_back(2.019E-05);
  v_th180.push_back(6.760E-06);
  v_th180.push_back(0.737E-10);

  v_fthksi.push_back(v_th000);
  v_fthksi.push_back(v_th010);
  v_fthksi.push_back(v_th020);
  v_fthksi.push_back(v_th030);
  v_fthksi.push_back(v_th040);
  v_fthksi.push_back(v_th050);
  v_fthksi.push_back(v_th060);
  v_fthksi.push_back(v_th070);
  v_fthksi.push_back(v_th080);
  v_fthksi.push_back(v_th090);
  v_fthksi.push_back(v_th100);
  v_fthksi.push_back(v_th110);
  v_fthksi.push_back(v_th120);
  v_fthksi.push_back(v_th130);
  v_fthksi.push_back(v_th140);
  v_fthksi.push_back(v_th150);
  v_fthksi.push_back(v_th160);
  v_fthksi.push_back(v_th170);
  v_fthksi.push_back(v_th180);
}

//
ReactionCoulex::~ReactionCoulex()
{

}

//
G4VParticleChange *PostStepDoIt(const G4Track &track, const G4Step &step)
{
  aParticleChange.Initialize(track);
  
  // Stop the current particle, if requested by G4UserLimits  
  if(reaction_here){
    reaction_here = false;
    G4DynamicParticle *projectile_out;
    G4DynamicParticle *recoil_out;
    projectile_out = new G4DynamicParticle();
    recoil_out = new G4DynamicParticle();
    
    if(SetupReactionProducts(track, projectile_out, recoil_out)){
      aParticleChange.ProposeTrackStatus(fStopAndKill);
      aParticleChange.SetNumberOfSecondaries(2);    
      aParticleChange.AddSecondary(projectile_out, pos_in, true);
      aParticleChange.AddSecondary(recoil_out, pos_in, true);
      aParticleChange.GetSecondary(0)->SetWeight(the_weight);
      aParticleChange.GetSecondary(1)->SetWeight(the_weight);
      sum_weights += the_weight;
      sum_proj++;
    }
  }
  
  return &aParticleChange;
}

//
G4double ReactionCoulex::PostStepGetPhysicalInteractionLength(const G4Track &track, G4double previous_step_size, G4ForceCondition *condition)
{
  reaction_here = false;
  *condition = NotForced;
  
  G4String name = track.GetVolume()->GetLogicalVolume()->GetName();
  
  if(name=="target_log"){
    G4UserLimits *user_limits = track.GetVolume()->GetLogicalVolume()->GetUserLimits();
    G4double z_reaction = user_limits->GetUserMinRange(track);
    G4double z_current = track.GetPosition().getZ();
    G4double z = z_reaction-z_current;
    if(z<0){
      // G4cout << " Past the reaction point" << G4endl;
      // G4cout << " Volume " << name << G4endl;
      // G4cout << " z[mm]: reaction " << z_reaction/mm << " current " << z_current/mm << " dz " << z/mm << G4endl;
      // getc(stdin);
      return DBL_MAX;
    }
    if(z>eps){
      G4ThreeVector dir = track.GetDynamicParticle()->GetMomentumDirection();
	      
      dir *= (z_reaction-z_current);
      // G4cout << " Before the reaction point" << G4endl;
      // G4cout << " Volume " << name <<G4endl;
      // G4cout << " z[mm]: reaction " << z_reaction/mm << " current " << z_current/mm << " dz " << z/mm << G4endl;
      // getc(stdin);
      return dir.mag();
    }
    if(z<=eps){ 
      reaction_here = true;
      // G4cout << setprecision(6) << "z_reaction: " << z_reaction << G4endl;
      // getc(stdin);
      track.GetVolume()->GetLogicalVolume()->GetUserLimits()->SetUserMinRange(-DBL_MAX);
      return 0.;
    }
  }

  return DBL_MAX;
}

//
G4bool ReactionCoulex::SetupReactionProducts(const G4Track &track, G4DynamicParticle *po, G4DynamicParticle *ro)
{
  G4double a_in;
  G4double z_in;
  G4ThreeVector dir_in, p_dir, r_dir, perp_in1, perp_in2;
  G4ThreeVector p_in;
  G4double ke_in;
  G4double theta;
  G4double e_prime;
  G4double t, tbar;
  G4double phi;
  G4double sint, cost, sinp, cosp;
  G4double p_par1, p_par2, p_perp, r;
  G4double ksi, f_ksi;
  G4double dc; // distance of closest approach in fm
  G4double sigma_ratio; // rxn depth/face
  G4double rand; // uniform RNG

  a_in = track.GetDynamicParticle()->GetDefinition()->GetAtomicMass();
  if(a_in != projectile_a){
    return false;
  }
  z_in = track.GetDynamicParticle()->GetDefinition()->GetAtomicNumber();
  if(z_in != projectile_z){
    return false;
  }
  po->SetDefinition(particle_projectile);
  ro->SetDefinition(particle_recoil);

  // check if energy in LAB is sufficienct for excitation
  // if so check that ksi and f(ksi) are good values
  // for good ksi and f(ksi) calculate ratio of XC at reaction energy
  // to ratio on face and use RNG to determine if reaction goes
  ke_in = track.GetDynamicParticle()->GetKineticEnergy(); // energy of the incident particle
  if(ke_in > dep){
    e_prime = ke_in-de*(projectile_a+recoil_a)/recoil_a; // internal energy of the center of mass 1/2*mu*Vrel^2
    ksi = GetKsi(ke_in);
    f_ksi = GetFKsi(ksi);
    if(f_ksi > 0.){
      sigma_ratio = e_prime*fksi/(e_prime_face*the_f);
      rand = G4UniformRand();
      if(rand < sigma_ratio){
	      // printf(" ke_in: %10.4f\n  xi: %10.4f\n f(xi): %10.4e\n", ke_in, ksi, f_ksi);
	      // printf("Cross section at reaction depth          : %10.4e b\n", sigma);
	      // printf("Cross section at face                    : %10.4e b\n", sigma_face);
	      // printf("Cross section ratio at reaction depth    : %10.4e\n", sigma_ratio);
	      // printf("For rand %10.4e and ratio %10.4e we will run a reaction!\n", rand, sigma_ratio);
      }else{
	      // printf("For rand %10.4e and ratio %10.4e skipping event... \n", rand, sigma_ratio);
	      drop_rand++;
	      return false;
      }
    }else{
      // printf("f(ksi) = %.2f --> sigma = 0 due to ksi = %.4f out of range (0,4)\n", fksi, ksi);
      drop_ksi++;
      return false;
    }
  }else{
    // printf("ke_in: %10.4f\n Not enough energy to excite projectile with DEp = %.4f! Skipping event...\n", ke_in, dep);
    drop_e++;
    return false;
  }
  // getc(stdin);

  // clear vectors needed
  v_thefth.clear();
  v_thbin.clear();
  v_fbin.clear();
  v_thlookup.clear();

  // setup lookup table for angular distribution of rxn products
  CalcFthKsi(ksi, &v_thefth); 
  SetupLookupGenerator(fksi); 

  // vector<G4double>::iterator it;
  // G4cout << "For ksi at reaction depth: " << ksi << G4endl;
  // G4cout << "Printing thefth" << G4endl;
  // for(it=v_thefth.begin();it!=v_thefth.end();it++){
  //   G4cout << (*it) << G4endl;
  // }

  // getc(stdin);

  // G4cout << "Printing thbin" << G4endl;
  // for(it=v_thbin.begin();it!=v_thbin.end();it++){
  //   G4cout<<(*it)<<G4endl;
  // }

  // getc(stdin);

  // G4cout << "Printing fbin" << G4endl;
  // for(it=v_fbin.begin();it!=v_fbin.end();it++){
  //   G4cout<<(*it)<<G4endl;
  // }

  // getc(stdin);

  // G4cout << "Printing thlookup with size " << thlookup.size() << G4endl;
  // vector<G4int>::iterator itt;
  // for(itt=thlookup.begin();itt<thlookup.end();itt++){
  //   G4cout<<(*it2)<<G4endl;
  // }

  // getc(stdin);
  
  dir_in = track.GetMomentumDirection();
  pos_in = track.GetPosition();
  p_in = track.GetMomentum(); 

  tbar = sqrt(ke_in/e_prime);
  t = projectile_a/recoil_a*tbar;
  // printf("tbar %f t %f\n", tbar, t);
  // getc(stdin);
  
  theta = GetTheta(); // in the CM
  // printf("theta = %.2f\n", theta);
  // getc(stdin);
  
  dc = 0.5*Ahc*projectile_z*recoil_z/ke_in*(1.+projectile_a/recoil_a)*(1.+1./std::sin(0.5*theta*Deg2Rad));
  // printf("dc %.4f\n", dc);
  // getc(stdin);
  
  if(dc > dcmin){      
    sint = std::sin(theta*deg);
    cost = std::cos(theta*deg);
    phi = CLHEP::twopi*G4UniformRand();
    sinp = std::sin(phi);
    cosp = std::cos(phi);
      
    // this is momentum in the lab assuming the z axis as the beam axis
    r = recoil_a/(projectile_a+recoil_a)*p_in.mag()/tbar;
    p_perpi = r*sint;
    p_par1 = r*(cost+t);
    p_par2 = r*(tbar-cost);
      
    //this is the rotation on the z-axis defined by the direction of the incoming projectile 
    perp_in1.setX(dir_in.getY());
    perp_in1.setY(dir_in.getX());
    perp_in1.setZ(0.);
    if(perp_in1.mag()==0.){
      perp_in1.setX(1.);
      perp_in1.setY(0.);
      perp_in1.setZ(0.);
      perp_in2.setX(0.);
      perp_in2.setY(1.);
      perp_in2.setZ(0.);
    }else{
      perp_in1.setMag(1.);
      perp_in2 = dir_in.cross(perp_in1);
    }
      
    p_dir = p_par1*dir_in + p_perp*cosp*perp_in1 + p_perp*sinp*perp_in2;
    r_dir = p_par2*dir_in - p_perp*cosp*perp_in1 - p_perp*sinp*perp_in2;
      
    po->SetMomentum(p_dir); 
    ro->SetMomentum(r_dir);

    the_weight = 1.0; // "weighted" by XC selection above, kept for ease-of-use

    return true;
  }  
  else
    return false;

}

//
void ReactionCoulex::TargetFaceCrossSection()
{
  G4cout << "---------- setup of decay products ----------" << G4endl;
  G4double projectile_t, recoil_t;
  G4double be2;
  G4double ke;
  G4double c, ce;
  
  projectile_a = projectile->GetA();
  projectile_z = projectile->GetZ(); 
  projectile_ex = projectile->GetEx()/MeV;
  projectile_t = projectile->GetTau()/ns*1000.; // in ps
  
  recoil_a = recoil->GetA();
  recoil_z = recoil->GetZ(); 
  recoil_ex = recoil->GetEx()/MeV;
  recoil_t = recoil->GetTau()/ns*1000.; // in ps
  
  printf("\nMinimum distance of closest approach: %5.2f fm\n", dc_min);
  
  if(projectile_ex*recoil_ex != 0.){
    printf("Simultaneous excitation of the projectile and target are not handled\n");
    exit(0);	     
  }
  if(projectile_ex+recoil_ex == 0.){
    printf("Excitation of either the projectile or the target has to be defined\n");
    exit(0);	     
  }
  
  if((projectile_ex > 0.) && (recoil_ex == 0.)){
    projectile_ex_flag = true;
    printf("projectile excitation\n");
    if(projectile_t > 0.){
      // from Eq. II A.56 multiplied by ahc (a = fine struct. const.)
      be2 = 5.0*0.08162025/projectile_t/pow(projectile_ex, 5.);
    }else{
      printf("Projectile de-excitation lifetime not defined %4.2f\n", projectile_t);
      exit(0);
    }
  }else{
    projectile_ex_flag = false;
    printf("Target recoil excitation\n");
    if(recoil_t > 0){
      // from Eq. II A.56 multiplied by ahc (a = fine struct. const.)
      be2 = 5.0*0.08162025/recoil_t/pow(recoil_ex,5.0);
    }else{
      printf("Target recoil de-excitation lifetime not defined %4.2f\n", recoil_t);
      exit(0);
    }
  }
  
  printf("projectile A : %5d\n", (int)projectile_a);
  printf("projectile Z : %5d\n", (int)projectile_z);
  if(projectile_ex_flag) {
    printf("projectile excitation energy : %5.3f MeV\n", projectile_ex);
    printf("projectile deexcitation lifetime : %5.2f ps\n", projectile_t);
    printf("projectile B(E2,0+=>2+) : %5.2f e^2b^2\n", be2);
  }

  printf("target recoil A : %5d\n", (int)recoil_a);
  printf("target recoil Z : %5d\n", (int)recoil_z);
  if(!projectile_ex_flag) {
    printf("target recoil excitation energy : %5.3f MeV\n", recoil_ex);
    printf("target recoil deexcitation lifetime : %5.2f ps\n", recoil_t);
    printf("target recoil B(E2,0+=>2+) : %5.2f e^2b^2\n", be2);
  }
  
  if(projectile_ex_flag){
    de = projectile_ex;
  }else{
    de = recoil_ex;
  }

  ke = projectile->GetKE(); // this is the kinetic energy of the projectile in the lab used to get the vi two lines down
  de_prime = (1.+projectile_a/recoil_a)*de;  // Eq. II C.4 and explanation below (CM internal energy 1/2*mu*Vrel^2)
  e_prime_face = ke-de_prime;
  ksi_face = GetKsi(ke);
  c = 4.819*projectile_a/recoil_z/recoil_z/(1.+projectile_a/recoil_a)/(1.+projectile_a/recoil_a); // Eq. II C.17 the case of E2 with Z1 instead of Z2, see Sec. II A.6
  ce = c*e_prime_face*be2; // Part of Eq. II C.15
  the_f = GetFKsi(ksi_ace); // from lookup table
  
  // clear vectors needed
  v_thefth.clear();
  v_thbin.clear();
  v_fbin.clear();
  v_thlookup.clear();

  Calcfthksi(ksi_face, &v_thefth); 
  SetupLookupGenerator(the_f); 

  // vector<G4double>::iterator it;
  // G4cout << "For ksi at reaction depth: " << ksi << G4endl;
  // G4cout << "Printing thefth" << G4endl;
  // for(it=v_thefth.begin();it!=v_thefth.end();it++){
  //   G4cout << (*it) << G4endl;
  // }

  // getc(stdin);

  // G4cout << "Printing thbin" << G4endl;
  // for(it=v_thbin.begin();it!=v_thbin.end();it++){
  //   G4cout<<(*it)<<G4endl;
  // }

  // getc(stdin);

  // G4cout << "Printing fbin" << G4endl;
  // for(it=v_fbin.begin();it!=v_fbin.end();it++){
  //   G4cout<<(*it)<<G4endl;
  // }

  // getc(stdin);

  // G4cout << "Printing thlookup with size " << thlookup.size() << G4endl;
  // vector<G4int>::iterator itt;
  // for(itt=thlookup.begin();itt<thlookup.end();itt++){
  //   G4cout<<(*it2)<<G4endl;
  // }

  // getc(stdin);

  sigma_face = ce*the_f; // Full Eq. II C.15, cross section on the target face in barns
  printf("target face xi :%10.4f\n", ksi_ace);
  printf("target face f(xi) :%10.4f\n", the_f);
  printf("target face cross section :%10.4f b\n", sigma_face);

  particle_projectile = G4IonTable::GetIonTable()->GetIon(projectile_z, projectile_a, projectile_ex);
  particle_recoil = G4IonTable::GetIonTable()->GetIon(recoil_z, recoil_a, recoil_ex);

  if(particle_projectile == nullptr){
    G4cerr << "Could not find outgoing projectile in the particle table " << projectile_z << " " << projectile_a << G4endl;
    exit(EXIT_FAILURE);
  }
  if(particle_recoil == nullptr) {
    G4cerr << "Could not find outgoing recoil in the particle table " << recoil_z << " " << recoil_a << G4endl;
    exit(EXIT_FAILURE);
  }
  
  if(projectile_ex_flag){
    particle_recoil->SetPDGStable(true);
    particle_projectile->SetPDGStable(false);
    particle_projectile->SetPDGLifeTime(projectile->GetTau());
    G4DecayTable *projectile_decay_table = particle_projectile->GetDecayTable();
    if(projectile_decay_table == nullptr){
      projectile_decay_table = new G4DecayTable();
      particle_projectile->SetDecayTable(projectile_decay_table);
    }
    GammaDecayChannel *projectile_decay = new GammaDecayChannel(-1, particle_projectile, 1, projectile_ex, projectile_ex, 0); // single step
    projectile_decay_table->Insert(projectile_decay);
    // projectile_decay_table->DumpInfo();
    // getc(stdin);

    // make sure that the projectile has the decay process in its manager
    if(particle_projectile->GetProcessManager() == nullptr) {
      G4cerr << "Could not find process manager for the projectile." << G4endl;
      exit(EXIT_FAILURE);
    }
    decay = new G4Decay();
    if(particle_projectile->GetProcessManager()->GetProcessActivation(decay) == false) {
      G4cout << "-> adding the projectile decay process" << G4endl;
      particle_projectile->GetProcessManager()->SetParticleType(particle_projectile);
      particle_projectile->GetProcessManager()->AddProcess(decay, 1, -1, 5);
    }      
     // particle_projectile->GetProcessManager()->DumpInfo();
     // getc(stdin);
  }else{
    particle_projectile->SetPDGStable(true);
    particle_recoil->SetPDGStable(false);
    particle_recoil->SetPDGLifeTime(recoil->GetTau());
    G4DecayTable *recoil_decay_table = particle_recoil->GetDecayTable(); 
    if(recoil_decay_table == nullptr) {
      recoil_decay_table = new G4DecayTable();
      particle_recoil->SetDecayTable(recoil_decay_table);
    }
    GammaDecayChannel *recoil_decay = new GammaDecayChannel(-1, particle_recoil, 1, recoil_ex, recoil_ex, 0); // single step
    recoil_decay_table->Insert(recoil_decay);
    // recoil_decay_table->DumpInfo();
    // getc(stdin);

    // make sure that the recoil has the decay process in its manager
    if(rec->GetProcessManager() == nullptr){
      G4cerr << "Could not find process manager for the recoil." << G4endl;
      exit(EXIT_FAILURE);
    }
    decay = new G4Decay();
    if(particle_recoil->GetProcessManager()->GetProcessActivation(decay) == false) {
      G4cout << "-> adding the recoil decay process" << G4endl;
      particle_recoil->GetProcessManager()->SetParticleType(particle_recoil);
      particle_recoil->GetProcessManager()->AddProcess(decay,1,-1,5);
    }
     // particle_recoil->GetProcessManager()->DumpInfo();
     // getc(stdin);
  }
  
  sum_weights = 0.0;
  sum_proj = 0; // good events
  drop_rand = 0; // dropped due to RNG < XC ratio
  drop_e = 0; // droppd due to energy requirement
  drop_ksi = 0; // dropped due to ksi limits

  // some legacy stuff?
  // not sure what the purpose is
  vector <G4double> *v_f = projectile->GetF();
  vector <G4double> *v_th = projectile->GetTh();
  for(int i=0;i<v_theta_array.size();i++){
    (*v_th)[i] = v_theta_array[i];
    (*v_f)[i] = DfofTheta(v_theta_array[i], &v_thefth);
  }

  projectile->SetTheF(the_f);

  G4cout << "---------- end of decay product setup ----------" << G4endl;

}

//
// for total XC fksi at given adiabaticity ksi, create a 
// lookup table of the differential XC as a function of 
// theta and ksi from previously determined differential 
// XC values as well as table of bin #s which samples this
// distribution
void ReactionCoulex::SetupLookupGenerator(G4double fksi)
{
  G4double f, slope;
  vector<G4int> v_limits;

  for(int i=1;i<(int)v_theta_array.size();i++){
    v_thbin.push_back(0.5*(v_theta_array[i-1]+v_theta_array[i]));
    f = v_thefth[i-1]*std::cos(v_theta_array[i-1]*Deg2Rad);
    f -= v_thefth[i]*std::cos(v_theta_array[i]*Deg2Rad);
    slope = v_thefth[i]-v_thefth[i-1];
    slope /= (v_theta_array[i]-v_theta_array[i-1]);
    slope / =Deg2Rad;
    f += slope*(std::sin(v_theta_array[i]*Deg2Rad)-std::sin(v_theta_array[i-1]*Deg2Rad));
    f *= CLHEP::twopi;
    v_fbin.push_back(f);
  }

  v_limits.push_back(0);
  f = 0.;
  for(i=0;i<(int)v_thbin.size();i++){
    f += v_fbin[i];
    v_limits.push_back(G4int(10000.*f/fksi));
  }

  for(int i=1;i<(int)v_limits.size();i++){
    for(int k=v_limits[i-1];k<v_limits[i];k++){
      v_thlookup.push_back(i-1);
    }
  } 
} 

// minimal possible calculation for determining ksi
G4double ReactionCoulex::GetKsi(G4double ke)
{
  G4double zeta, sqz, eti, etf, ksi;
  zeta = dep/ke; // Eq. II C.5 dimensionless
  sqz = std::sqrt(1.-zeta);
  eti = 0.5*projectile_z*recoil_z*sqrt(projectile_a/10.008/ke); // Eq. II C.8
  etf = eti/sqz; // Eq. II C.9
  ksi = etf-eti; // by definition
  return ksi;
}

// returns the scattering angle in the CM according to Tab. II.8 p. 464
G4double ReactionCoulex::GetTheta()
{
  G4double x_eps=0.0001;
  G4int bin;
  G4double th1, th2, f1, f2, f, r, x1, x2, y1, y2, y;
  G4double th;
  // first look up the bin
  bin = v_thlookup[(G4int)(G4UniformRand()*v_thlookup.size())];
  th1 = v_theta_array[bin];
  th2 = v_theta_array[bin+1];
  f1 = v_thefth[bin];
  f2 = v_thefth[bin+1];

  f = v_fbin[bin]/CLHEP::twopi;
  r = G4UniformRand();
 
  x1 = th1;
  y1 = FineThetaFunction(x1, th1, th2, f1, f2, f, r);
  if(std::fabs(y1) < x_eps) return th1;

  x2 = th2;
  y2 = FineThetaFunction(x2,th1,th2,f1,f2,F,r);
  if(std::fabs(y2) < x_eps) return th2;

  th = v_thbin[bin];
  while(std::fabs(y=FineThetaFunction(th, th1, th2, f1, f2, f, r)) > x_eps) {
    if(y < 0){ 
      x1 = th;
      y1 = y;
    }
    if(y >= 0){
      x2 = th;
      y2 = y;
    }
    th = x1-y1*(x2-x1)/(y2-y1);
  }
  return th;
}

//
G4double ReactionCoulex::FineThetaFunction(G4double th, G4double th1, G4double th2, G4double f1, G4double f2, G4double ff, G4double r)
{
  G4double f, g, dth, df;
  dth = th2-th1;
  df = f2-f1;
  f = f1+(th-th1)*df/dth;
  g = f1*std::cos(th1*Deg2Rad)-f*std::cos(th*Deg2Rad)+df/dth/Deg2Rad*(std::sin(th*Deg2Rad)-std::sin(th1*Deg2Rad));
  return g/ff-r;
}

//
G4double ReactionCoulex::DfdOmega(G4double ksi, G4double theta)
{
  vector<G4double> *v_fth = new vector<G4double>;
  if(CalcFthKsi(ksi, v_fth)){ // 0 if ksi out of range
    G4double df_t = DfofTheta(theta, v_fth);
    delete v_fth; // free the memory
    return df_t;
  }else{
    delete v_fth;
    return 0.;
  }
}

//
G4double ReactionCoulex::DfofTheta(G4double theta, vector<G4double> *v_fth)
{
  G4double x1, y1, x2, y2, x, y;

  // G4cout << "Printing thefth" << G4endl;
  // vector<G4double>::iterator it;
  // for(it=v_fth->begin();it<v_fth->end();it++){
  //   G4cout<<(*it)<<G4endl;
  // }
  // getc(stdin);

  for(int i=1;i<(int)v_theta_array.size();i++){
    if((theta>=v_theta_array[i-1]) && (theta<v_theta_array[i])){
      break;
    }
  }
  x1 = v_theta_array[i-1];
  y1 = (*v_fth)[i-1];
  x2 = v_theta_array[i];
  y2 = (*v_fth)[i];
  x = theta;
  y = y1+(y2-y1)*(x-x1)/(x2-x1);
  return y;
}

//
G4int ReactionCoulex::CalcFthKsi(G4double ksi, vector<G4double> *v_fth)
{
  G4int shift;
  G4double x1, x2, y1, y2, y, dx;

  // return 0 if out of range of lookup table
  if((ksi<=0.0) || (ksi>=4.0)) return 0;

  shift = 0;
  std::vector<G4double>::iterator it_ksi;
  for(it_ksi=v_ksi_array;it_ksi!=(v_ksi_array.end()-1);it_ksi++){
    if((ksi>=(*it_ksi)) && (ksi<=(*(it_ksi+1)))){
	    break;
    }
    shift++;
  }
  x1 = *it_ksi;
  x2 = *(it_ksi+1);
  dx = x2-x1;

  std::vector<G4double>::iterator it;
  std::vector<std::vector<G4double>>::iterator it_fthksi;
  for(it_fthksi=v_fthksi.begin();it_fthksi<v_fthksi.end();it_fthksi++){
    it = (*it_fthksi).begin();
    y1 = *(it+shift);
    y2 = *(it+shift+1);
    y = y1+(y2-y1)/dx*(ksi-x1);
    v_fth->push_back(y);
  }

  // G4cout << "Printing thefth for ksi " << ksi << G4endl;
  // for(it=v_fth.begin();it!=v_fth.end();it++){
  //   G4cout<<(*it)<<G4endl;
  // }
  // getc(stdin);

  return 1;
}

//
G4double ReactionCoulex::GetFKsi(G4double ksi)
{
  G4int shift;
  G4double fksi;
  G4double x1, x2, y1, y2, dx, dy;

  // return 0 if out of range of lookup table
  if((ksi<=0.) && (ksi>=4.)) return 0;
  
  std::vector<G4double>::iterator it;
  for(it=v_ksi_array.begin();it!=v_ksi_array.end()-1;it++){
    if((ksi>=(*it)) && (ksi<=(*(it+1)))){
      break;
    }
    shift++;
  }
  x1 = *it;
  x2 = *(it+1);
  dx = x2-x1;
  it = v_fksi_array.begin();
  y1 = *(it+shift);
  y2 = *(it+shift+1);
  dy = y2-y1;    
  fksi = y1+(ksi-x1)*dy/dx;    
  // G4cout << setprecision(6);
  // G4cout << "ksi: " << ksi << G4endl;
  // G4cout << "x1: " << x1 << " x2: " << x2 << " dx: " << dx << " shift: " << shift << G4endl;
  // G4cout << "y1: " << y1 << " y2: " << y2 << " dy: " << dy << G4endl;
  // G4cout << "fksi: " << fksi << G4endl;
  // getc(stdin);
  
  return fksi;
}

