//---NOTE
//This is a ICAL Geometry setup consisting of 151 iron layers and 150 glass layers.
//The dimension of Iron layer is 16m*16m*5.6cm .
//The dimension of Glass layer is given by 16m*16m* 0.001cm.
//The inter layer gap is 4cm .So the gap between an iron and glass layer is 2cm.
//Iron layer has been placed at the top.
 // \author Hemalata Nayak
#include "TGeoManager.h"
#include "TGeoMaterial.h" 
#include "TGeoMedium.h"
#include "TGeoVolume.h" 
#include "TGeoBBox.h" 
#include "TGeoCompositeShape.h" 
#include "TGeoBoolNode.h" 
#include "TGeoPhysicalNode.h" 
#include "TGeoMatrix.h"
#include <iostream> 
// #include "TGeoMagneticField.h"


void rpc_geom(bool vis = true)
{
   
   TGeoManager *geom = new TGeoManager("rpc_geometry", "rpc_geometry");

//    //--- define some materials
   TGeoMaterial *matAir = new TGeoMaterial("Air", 1,1,0.001205);
   TGeoMaterial *matGlass = new TGeoMaterial("Glass", 28.09,14,2.5);
   TGeoMaterial *matAl = new TGeoMaterial("Al", 26.98,13,2.7);
   

//    //--- define media
   TGeoMedium *Air = new TGeoMedium("Air",1, matAir);
   TGeoMedium *Glass = new TGeoMedium("Glass",3, matGlass);
   TGeoMedium *Al = new TGeoMedium("Root Material",2, matAl);
//   // All Units in cm
 
   //--- make the top World volume //---All units are in cm
   Double_t worldx = 50.1;
   Double_t worldy = 50.1;
   Double_t worldz =  93.000605; //64.89466;
   TGeoVolume *top = geom->MakeBox("TOP", Air , worldx, worldy, worldz);
   geom->SetTopVolume(top);
   // geom->SetVisibility(kFALSE);

   // half-thickness of objects in the geometry
   Double_t rpcDim = 50; // cm, half of x or y dimension of each layer
   Double_t glass_sen_Thick = 0.000005; // cm (proxy for RPC, only used for position and time sensing)
   Double_t glassThickness= 0.3; //cm
   Double_t AlThickness = 0.15; //cm
   
   Double_t inter_layer_gap = 15.79989;//cm
   Double_t Gsen_G_gap= 0.1; //cm
   Double_t G_Al_gap= 0.0001; //cm
   int nlayers = 12;

   //---Creating Glass_sensitive layers

   TGeoVolume *Glass_sen = geom->MakeBox("Glass_sen", Glass, rpcDim, rpcDim, glass_sen_Thick);
   Glass_sen->SetLineColor(kBlue);
   Glass_sen->SetTransparency(0.9);
   // top->AddNode(IRON,1, new TGeoTranslation(0, 0, 2.8));
 
   for(int i=0;i<nlayers;i++){
   Double_t Gsens_layerPosition=(((glass_sen_Thick*2)+Gsen_G_gap+G_Al_gap+(AlThickness*2) +inter_layer_gap+(glassThickness*2))*i);
   top->AddNode(Glass_sen,i+1, new TGeoTranslation(0, 0, -Gsens_layerPosition+ 92.900605));
   cout << "The G_sens position on z-axis (in cm) is " <<  Gsens_layerPosition << endl;
   }


   
   //---Creating Glass layers

   TGeoVolume *GLASS = geom->MakeBox("GLASS", Glass, rpcDim, rpcDim, glassThickness);
   GLASS->SetLineColor(kRed);
   GLASS->SetTransparency(0.9);
   // top->AddNode(GLASS,1, new TGeoTranslation(0, 0, -2.1));
   
   for(int j=0;j<nlayers;j++){
   Double_t glasslayerPosition=((Gsen_G_gap+(glass_sen_Thick*2)+inter_layer_gap+(AlThickness*2)+G_Al_gap+(glassThickness*2))*j)+((glass_sen_Thick)+Gsen_G_gap+ glassThickness);//the starting position of any layer will be for its centre
    top->AddNode(GLASS,j+1, new TGeoTranslation(0, 0, -glasslayerPosition +92.900605));
    cout << "The Glass layer position on z-axis (in cm) is " <<  glasslayerPosition  << endl;
    }  
//---Creating Aluminium layers

   TGeoVolume *Aluminium = geom->MakeBox("Aluminium", Al, rpcDim, rpcDim, AlThickness);
   Aluminium->SetLineColor(kGreen);
   Aluminium->SetTransparency(0.9);
   // top->AddNode(GLASS,1, new TGeoTranslation(0, 0, -2.1));
   
   for(int k=0;k<nlayers;k++){
   Double_t Al_layerPosition=((AlThickness*2 +inter_layer_gap+(glass_sen_Thick*2) +Gsen_G_gap+(glassThickness*2)+G_Al_gap)*k)+((glass_sen_Thick)+Gsen_G_gap+(glassThickness*2)+G_Al_gap+AlThickness);
    top->AddNode(Aluminium,k+1, new TGeoTranslation(0, 0,-Al_layerPosition +92.900605));
   } // the second term in each for loop in position variable is for defining the starting position of the centre of each layer (i.e. when i or j or k is 0)



   geom->CloseGeometry();
   geom->Export("rpc_geom.root");
   geom->Export("rpc_geom.gdml");
   // disable sections to save only part of geometry

   //--- draw the ROOT box.
   // by default the picture will appear in the standard ROOT TPad.
   //if you have activated the following line in system.rootrc,
   //it will appear in the GL viewer
   //#Viewer3D.DefaultDrawOption:   ogl

   geom->SetVisLevel(4);
   if (vis) top->Draw("ogle");
}
