
void profile()
{
   auto c1 = new TCanvas("c1","Profile histogram example",200,10,700,500);
   auto hprof2d  = new TProfile2D("hprof2d","Profile of pz versus px and py",40,-4,4,40,-4,4,0,20);
   
   // auto prof = new TProfile ("profile hist", "scattering angle", 100, 0, 0.05, 0, 0.004, Option_t *option="") //added later for theta profile
   Float_t px, py, pz;
   // Float_t mu_x, mu_y, mu_z;

   // for ( Int_t i=0; i<25000; i++) {
   //    gRandom->Rannor(px,py);
   //    pz = px*px + py*py;
   //    hprof2d->Fill(px,py,pz,1);
   // }
   for ( Int_t i=0; i<25000; i++) {
      gRandom->Rannor(px,py);
      pz = px*px + py*py;
      hprof2d->Fill(px,py,pz,1);
   }
   hprof2d->Draw();
   // prof->Draw();
}