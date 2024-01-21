//
#define S3_R1 11.
#define S3_R2 35.

void s3_distance2angle(double front_dis=20., double back_dis=20.)
{
  // downstream
  double a = S3_R1/front_dis;
  double a_angle = atan(a)/3.14159*180.;
  double b = S3_R2/front_dis;
  double b_angle = atan(b)/3.14159*180.;

  cout << "down stream" << endl;
  cout << a_angle << " to " << b_angle << endl;

  // upstream
  double c = S3_R1/back_dis;
  double c_angle = atan(c)/3.14159*180.;
  double d = S3_R2/back_dis;
  double d_angle = atan(d)/3.14159*180.;

  cout << "up stream" << endl;
  cout << 180.-d_angle << " to " << 180.-c_angle << endl;
}
