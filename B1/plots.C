void plots()
{
TFile *f = new TFile("mu_e.root");
TTree *t = (TTree*)f->Get("mu_e_scatt");
TCanvas *c = new TCanvas();
//t->Draw("acos(-mu_z/sqrt(mu_x^2+mu_y^2+mu_z^2))");
//t->Draw("acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))");
c->Divide(2,2);
c->cd(1);
t->Draw("acos(-mu_z/sqrt(mu_x^2+mu_y^2+mu_z^2)):acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))","acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))<0.3","profn");

//t->Draw("mu_E:acos(-mu_z/sqrt(mu_x^2+mu_y^2+mu_z^2)):acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))","acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))<0.3","PROFNCOLZ");
//t->Draw("electron_E");


// c->cd(2);
// // t->Draw("acos(e_z/sqrt(e_x^2+e_y^2))");
// t->Draw("acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2)):mu_E","acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))<0.03","prof");

// c->cd(3);
// t->Draw("acos(-mu_z/sqrt(mu_x^2+mu_y^2+mu_z^2)):acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))");

c->cd(4);
t->Draw("electron_E:acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))","acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))<0.3 && electron_E>200   ","prof");
//t->Draw("mu_E:acos(-mu_z/sqrt(mu_x^2+mu_y^2+mu_z^2))","acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))<0.3 && electron_E>200   ","prof");
//t->Draw("mu_E:electron_E","acos(-e_z/sqrt(e_x^2+e_y^2+e_z^2))<0.03 && electron_E>2000","prof");

}