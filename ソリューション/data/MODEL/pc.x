xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 120;
 -7.76042;10.17623;4.29614;,
 7.36580;10.17623;4.29614;,
 7.36580;2.18519;3.68703;,
 -7.76042;2.18519;3.68703;,
 7.36580;10.17623;4.29614;,
 7.36580;10.16462;4.65422;,
 7.36580;2.17356;4.04511;,
 7.36580;2.18519;3.68703;,
 7.36580;10.16462;4.65422;,
 -7.76042;10.16462;4.65422;,
 -7.76042;2.17356;4.04511;,
 7.36580;2.17356;4.04511;,
 -7.76042;10.16462;4.65422;,
 -7.76042;10.17623;4.29614;,
 -7.76042;2.18519;3.68703;,
 -7.76042;2.17356;4.04511;,
 7.36580;10.17623;4.29614;,
 -7.76042;10.17623;4.29614;,
 -7.76042;2.18519;3.68703;,
 7.36580;2.18519;3.68703;,
 -0.77795;2.32084;3.84840;,
 0.70973;2.32084;3.84840;,
 0.70973;-0.05502;3.84840;,
 -0.77795;-0.05502;3.84840;,
 0.70973;2.32084;3.84840;,
 0.70973;2.32084;4.17016;,
 0.70973;-0.05502;4.17016;,
 0.70973;-0.05502;3.84840;,
 0.70973;2.32084;4.17016;,
 -0.77795;2.32084;4.17016;,
 -0.77795;-0.05502;4.17016;,
 0.70973;-0.05502;4.17016;,
 -0.77795;2.32084;4.17016;,
 -0.77795;2.32084;3.84840;,
 -0.77795;-0.05502;3.84840;,
 -0.77795;-0.05502;4.17016;,
 0.70973;2.32084;3.84840;,
 -0.77795;2.32084;3.84840;,
 -0.77795;-0.05502;3.84840;,
 0.70973;-0.05502;3.84840;,
 -2.72500;0.30092;2.92508;,
 2.27379;0.30092;2.92508;,
 2.27379;-0.02896;2.92508;,
 -2.72500;-0.02896;2.92508;,
 2.27379;0.30092;2.92508;,
 2.27379;0.30092;4.97219;,
 2.27379;-0.02896;4.97219;,
 2.27379;-0.02896;2.92508;,
 2.27379;0.30092;4.97219;,
 -2.72500;0.30092;4.97219;,
 -2.72500;-0.02896;4.97219;,
 2.27379;-0.02896;4.97219;,
 -2.72500;0.30092;4.97219;,
 -2.72500;0.30092;2.92508;,
 -2.72500;-0.02896;2.92508;,
 -2.72500;-0.02896;4.97219;,
 2.27379;0.30092;2.92508;,
 -2.72500;0.30092;2.92508;,
 -2.72500;-0.02896;2.92508;,
 2.27379;-0.02896;2.92508;,
 -3.99702;0.41120;-6.10656;,
 3.49013;0.41120;-6.10656;,
 3.49013;-0.03638;-6.10656;,
 -3.99702;-0.03638;-6.10656;,
 3.49013;0.41120;-6.10656;,
 3.49013;0.41120;-1.92934;,
 3.49013;-0.03638;-1.92934;,
 3.49013;-0.03638;-6.10656;,
 3.49013;0.41120;-1.92934;,
 -3.99702;0.41120;-1.92934;,
 -3.99702;-0.03638;-1.92934;,
 3.49013;-0.03638;-1.92934;,
 -3.99702;0.41120;-1.92934;,
 -3.99702;0.41120;-6.10656;,
 -3.99702;-0.03638;-6.10656;,
 -3.99702;-0.03638;-1.92934;,
 3.49013;0.41120;-6.10656;,
 -3.99702;0.41120;-6.10656;,
 -3.99702;-0.03638;-6.10656;,
 3.49013;-0.03638;-6.10656;,
 9.37934;11.57962;-2.65696;,
 16.02183;11.57962;-2.65696;,
 16.02183;0.19637;-2.65696;,
 9.37934;0.19637;-2.65696;,
 16.02183;11.57962;-2.65696;,
 16.02183;11.57962;7.69708;,
 16.02183;0.19637;7.69708;,
 16.02183;0.19637;-2.65696;,
 16.02183;11.57962;7.69708;,
 9.37934;11.57962;7.69708;,
 9.37934;0.19637;7.69708;,
 16.02183;0.19637;7.69708;,
 9.37934;11.57962;7.69708;,
 9.37934;11.57962;-2.65696;,
 9.37934;0.19637;-2.65696;,
 9.37934;0.19637;7.69708;,
 16.02183;11.57962;-2.65696;,
 9.37934;11.57962;-2.65696;,
 9.37934;0.19637;-2.65696;,
 16.02183;0.19637;-2.65696;,
 5.64935;0.04707;-5.75527;,
 6.46619;0.04707;-5.56669;,
 6.46619;-0.03453;-5.56669;,
 5.64935;-0.03453;-5.75527;,
 6.46619;0.04707;-5.56669;,
 5.85373;0.04707;-3.97852;,
 5.85373;-0.03453;-3.97852;,
 6.46619;-0.03453;-5.56669;,
 5.85373;0.04707;-3.97852;,
 5.45011;0.04707;-4.07170;,
 5.45011;-0.03453;-4.07170;,
 5.85373;-0.03453;-3.97852;,
 5.45011;0.04707;-4.07170;,
 5.64935;0.04707;-5.75527;,
 5.64935;-0.03453;-5.75527;,
 5.45011;-0.03453;-4.07170;,
 6.46619;0.04707;-5.56669;,
 5.64935;0.04707;-5.75527;,
 5.64935;-0.03453;-5.75527;,
 6.46619;-0.03453;-5.56669;;
 
 36;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;;
 
 MeshMaterialList {
  8;
  36;
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.163200;0.800000;0.000000;1.000000;;
   33.000000;
   0.570000;0.570000;0.570000;;
   0.012240;0.060000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.517600;0.300800;0.037600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.194400;0.194400;0.194400;1.000000;;
   23.000000;
   0.190000;0.190000;0.190000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.483200;0.483200;0.483200;1.000000;;
   23.000000;
   0.310000;0.310000;0.310000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.571200;0.571200;0.571200;1.000000;;
   23.000000;
   0.170000;0.170000;0.170000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.276000;0.276000;0.276000;1.000000;;
   23.000000;
   0.310000;0.310000;0.310000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  14;
  0.000000;0.076004;-0.997108;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.076003;0.997108;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.224948;0.000000;-0.974371;,
  0.933025;0.000000;0.359811;,
  -0.224944;0.000000;0.974372;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.999475;0.032405;,
  0.000000;-0.999473;-0.032462;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.993070;0.000000;-0.117524;;
  36;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;13,13,13,13;,
  4;11,11,11,11;,
  4;12,12,12,12;;
 }
 MeshTextureCoords {
  120;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
