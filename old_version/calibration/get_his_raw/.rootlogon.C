/// \file
/// \ingroup Tutorials
/// Example of `rootlogon.C`.
/// The macro `rootlogon.C` in the current working directory, is executed when
/// `root` starts unless the option `-n` is used.
///
/// \macro_code
///
/// \author Rene Brun

{
  gROOT->ProcessLine(".L XIA_Decode_cpp.so");
}


