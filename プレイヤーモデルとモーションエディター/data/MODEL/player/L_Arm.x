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
 35;
 0.41892;-0.59168;-0.10543;,
 1.13331;-0.68676;-0.10412;,
 0.45359;-0.50836;0.73995;,
 1.13162;-0.78622;0.73963;,
 0.38160;-0.11934;-0.75250;,
 1.13255;0.01577;-0.81634;,
 0.36572;0.36707;-0.48707;,
 1.13246;0.43294;-0.52271;,
 0.35415;0.58848;0.11103;,
 1.13365;0.77997;0.03945;,
 0.43773;0.43708;0.65336;,
 1.13054;0.36751;0.68220;,
 4.22606;-0.19791;-0.07503;,
 4.22561;0.06820;-0.48953;,
 4.22556;0.22622;-0.31864;,
 1.13365;0.77997;0.03945;,
 4.22625;0.35766;0.00853;,
 1.13054;0.36751;0.68220;,
 4.22444;0.20144;0.38260;,
 1.13162;-0.78622;0.73963;,
 4.22507;-0.23558;0.41603;,
 4.43954;0.07988;-0.03325;,
 4.22556;0.22622;-0.31864;,
 4.22625;0.35766;0.00853;,
 4.22606;-0.19791;-0.07503;,
 4.22561;0.06820;-0.48953;,
 4.22507;-0.23558;0.41603;,
 4.22444;0.20144;0.38260;,
 0.00474;-0.00160;0.00280;,
 0.43773;0.43708;0.65336;,
 0.35415;0.58848;0.11103;,
 0.41892;-0.59168;-0.10543;,
 0.45359;-0.50836;0.73995;,
 0.38160;-0.11934;-0.75250;,
 0.36572;0.36707;-0.48707;;
 
 36;
 3;0,1,2;,
 3;2,1,3;,
 3;0,4,1;,
 3;1,4,5;,
 3;4,6,5;,
 3;5,6,7;,
 3;6,8,7;,
 3;7,8,9;,
 3;8,10,9;,
 3;9,10,11;,
 3;10,2,11;,
 3;11,2,3;,
 3;1,5,12;,
 3;12,5,13;,
 3;5,7,13;,
 3;13,7,14;,
 3;15,16,7;,
 3;7,16,14;,
 3;17,18,15;,
 3;15,18,16;,
 3;19,20,17;,
 3;17,20,18;,
 3;19,1,20;,
 3;20,1,12;,
 3;21,22,23;,
 3;21,24,25;,
 3;21,25,22;,
 3;21,26,24;,
 3;21,23,27;,
 3;21,27,26;,
 3;28,29,30;,
 3;28,31,32;,
 3;28,32,29;,
 3;28,33,31;,
 3;28,30,34;,
 3;28,34,33;;
 
 MeshMaterialList {
  1;
  36;
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
  0,
  0;;
  Material {
   0.800000;0.659200;0.489600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  29;
  -0.111477;-0.986908;-0.116558;,
  0.086328;-0.755948;-0.648915;,
  -0.009791;0.799880;-0.600080;,
  0.063140;0.357964;0.931598;,
  -0.016893;-0.941559;-0.336423;,
  -0.010295;0.990450;0.137487;,
  0.490316;0.594833;0.636997;,
  0.406653;0.060365;0.911586;,
  0.430845;0.894432;-0.119849;,
  0.426514;-0.820625;-0.380342;,
  0.481134;0.742801;-0.465571;,
  0.456159;-0.748629;-0.481117;,
  0.892094;0.451633;0.013986;,
  -0.467107;-0.883698;0.029817;,
  -0.549481;0.678658;0.487334;,
  -0.528603;-0.824137;-0.203413;,
  -0.513932;0.849513;-0.119172;,
  -0.309537;-0.744607;-0.591395;,
  -0.466065;0.628118;-0.623098;,
  -0.937874;0.345309;0.033962;,
  -0.560307;0.382589;-0.734630;,
  -0.056680;0.542222;-0.838321;,
  -0.032335;0.090620;0.995360;,
  -0.319069;0.065522;0.945464;,
  0.058054;0.049686;0.997076;,
  0.359331;0.631177;-0.687384;,
  0.396437;-0.914239;-0.083690;,
  0.791372;-0.578387;-0.197989;,
  -0.822827;-0.555887;-0.118090;;
  36;
  3;15,4,13;,
  3;13,4,0;,
  3;15,17,4;,
  3;4,17,1;,
  3;20,18,21;,
  3;21,18,2;,
  3;18,16,2;,
  3;2,16,5;,
  3;16,14,5;,
  3;5,14,3;,
  3;22,23,3;,
  3;3,23,24;,
  3;4,1,9;,
  3;9,1,11;,
  3;21,2,25;,
  3;25,2,10;,
  3;5,8,2;,
  3;2,8,10;,
  3;3,6,5;,
  3;5,6,8;,
  3;24,7,3;,
  3;3,7,6;,
  3;0,4,26;,
  3;26,4,9;,
  3;12,10,8;,
  3;27,9,11;,
  3;12,25,10;,
  3;27,26,9;,
  3;12,8,6;,
  3;12,6,7;,
  3;19,14,16;,
  3;28,15,13;,
  3;19,23,14;,
  3;28,17,15;,
  3;19,16,18;,
  3;19,18,20;;
 }
 MeshTextureCoords {
  35;
  0.250000;0.875000;,
  -0.000000;1.000000;,
  0.125000;0.875000;,
  0.045270;0.946100;,
  0.375000;0.875000;,
  0.226540;0.930120;,
  0.375000;0.750000;,
  0.262370;0.907510;,
  0.250000;0.750000;,
  0.205620;0.883750;,
  0.125000;0.750000;,
  0.093060;0.820350;,
  -0.000000;1.000000;,
  0.226540;0.930120;,
  0.262370;0.907510;,
  0.258050;0.989040;,
  0.258050;0.989040;,
  0.284350;0.989900;,
  0.284350;0.989900;,
  -0.000000;1.000000;,
  -0.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;;
 }
}
