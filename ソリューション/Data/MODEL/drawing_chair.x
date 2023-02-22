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
 72;
 -26.38427;14.66378;-21.17372;,
 -23.75737;14.66378;-21.17372;,
 -23.75737;-0.38718;-21.17372;,
 -26.38427;-0.38718;-21.17372;,
 -23.75737;14.66378;-19.18696;,
 -23.75737;-0.38718;-19.18696;,
 -26.38427;14.66378;-19.18696;,
 -26.38427;-0.38718;-19.18696;,
 23.89066;14.66378;-21.17372;,
 26.51756;14.66378;-21.17372;,
 26.51756;-0.38718;-21.17372;,
 23.89066;-0.38718;-21.17372;,
 26.51756;14.66378;-19.18696;,
 26.51756;-0.38718;-19.18696;,
 23.89066;14.66378;-19.18696;,
 23.89066;-0.38718;-19.18696;,
 23.94111;14.66378;-0.99337;,
 26.56801;14.66378;-0.99337;,
 26.56801;-0.38718;-0.99337;,
 23.94111;-0.38718;-0.99337;,
 26.56801;14.66378;0.99337;,
 26.56801;-0.38718;0.99337;,
 23.94111;14.66378;0.99337;,
 23.94111;-0.38718;0.99337;,
 -26.40635;14.66378;-0.99337;,
 -23.77947;14.66378;-0.99337;,
 -23.77947;-0.38718;-0.99337;,
 -26.40635;-0.38718;-0.99337;,
 -23.77947;14.66378;0.99337;,
 -23.77947;-0.38718;0.99337;,
 -26.40635;14.66378;0.99337;,
 -26.40635;-0.38718;0.99337;,
 -15.37866;16.41243;-21.45138;,
 -15.37866;13.52443;-21.45138;,
 -30.30174;13.52443;-21.45138;,
 -30.30174;16.41243;-21.45138;,
 -15.37866;16.41243;0.99295;,
 -30.30174;16.41243;0.99295;,
 -30.30174;13.52443;0.99295;,
 -15.37866;13.52443;0.99295;,
 1.67495;16.41243;-21.45137;,
 1.67495;13.52443;-21.45137;,
 1.67495;16.41243;0.99295;,
 1.67495;13.52443;0.99295;,
 17.86474;16.41243;0.99295;,
 17.86474;13.52443;0.99295;,
 29.50485;13.52443;0.99295;,
 29.50485;16.41243;0.99295;,
 17.86474;16.41243;-21.45138;,
 29.50485;16.41243;-21.45138;,
 29.50485;13.52443;-21.45138;,
 17.86474;13.52443;-21.45138;,
 -30.30174;16.41243;-5.58839;,
 -15.37866;16.41243;-5.58839;,
 -30.30174;13.52443;-5.58839;,
 1.67495;16.41243;-5.58839;,
 -15.37866;13.52443;-5.58839;,
 17.86474;16.41243;-5.58839;,
 1.67495;13.52443;-5.58839;,
 29.50485;16.41243;-5.58839;,
 17.86474;13.52443;-5.58839;,
 29.50485;13.52443;-5.58839;,
 -30.30174;16.41243;-14.03737;,
 -15.37866;16.41243;-14.03737;,
 -30.30174;13.52443;-14.03737;,
 1.67495;16.41243;-14.03737;,
 -15.37866;13.52443;-14.03737;,
 17.86474;16.41243;-14.03737;,
 1.67495;13.52443;-14.03737;,
 29.50485;16.41243;-14.03737;,
 17.86474;13.52443;-14.03737;,
 29.50485;13.52443;-14.03737;;
 
 62;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,0,3,7;,
 4;6,4,1,0;,
 4;3,2,5,7;,
 4;8,9,10,11;,
 4;9,12,13,10;,
 4;12,14,15,13;,
 4;14,8,11,15;,
 4;14,12,9,8;,
 4;11,10,13,15;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;22,16,19,23;,
 4;22,20,17,16;,
 4;19,18,21,23;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;28,30,31,29;,
 4;30,24,27,31;,
 4;30,28,25,24;,
 4;27,26,29,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,33,32;,
 4;42,36,39,43;,
 4;44,42,43,45;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;48,51,41,40;,
 4;52,37,36,53;,
 4;52,54,38,37;,
 4;53,36,42,55;,
 4;54,56,39,38;,
 4;55,42,44,57;,
 4;56,58,43,39;,
 4;57,44,47,59;,
 4;58,60,45,43;,
 4;59,47,46,61;,
 4;60,61,46,45;,
 4;62,52,53,63;,
 4;62,63,32,35;,
 4;62,35,34,64;,
 4;62,64,54,52;,
 4;63,53,55,65;,
 4;63,65,40,32;,
 4;64,34,33,66;,
 4;64,66,56,54;,
 4;65,55,57,67;,
 4;65,67,48,40;,
 4;66,33,41,68;,
 4;66,68,58,56;,
 4;67,57,59,69;,
 4;67,69,49,48;,
 4;68,41,51,70;,
 4;68,70,60,58;,
 4;69,59,61,71;,
 4;69,71,50,49;,
 4;70,51,50,71;,
 4;70,71,61,60;;
 
 MeshMaterialList {
  2;
  62;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\table_wood_01.jpeg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.960000;0.960000;0.960000;;
   0.690000;0.690000;0.690000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\sofa_reg.jpeg";
   }
  }
 }
 MeshNormals {
  15;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;;
  62;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;8,8,6,6;,
  4;7,7,7,7;,
  4;9,9,8,8;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;10,6,6,10;,
  4;10,10,9,9;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;11,11,11,11;,
  4;13,13,13,13;,
  4;11,11,11,11;,
  4;13,13,13,13;,
  4;11,11,11,11;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;12,12,12,12;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;13,13,13,13;;
 }
 MeshTextureCoords {
  72;
  0.065502;0.605487;,
  0.109426;0.605487;,
  0.109426;5.817032;,
  0.065502;5.817032;,
  0.109426;0.605487;,
  0.109426;5.817032;,
  0.065502;0.605487;,
  0.065502;5.817032;,
  0.906128;0.605487;,
  0.950051;0.605487;,
  0.950051;5.817032;,
  0.906128;5.817032;,
  0.950051;0.605487;,
  0.950051;5.817032;,
  0.906128;0.605487;,
  0.906128;5.817032;,
  0.906971;0.605487;,
  0.950894;0.605487;,
  0.950894;5.817032;,
  0.906971;5.817032;,
  0.950894;0.605487;,
  0.950894;5.817032;,
  0.906971;0.605487;,
  0.906971;5.817032;,
  0.065133;0.605487;,
  0.109056;0.605487;,
  0.109056;5.817032;,
  0.065133;5.817032;,
  0.109056;0.605487;,
  0.109056;5.817032;,
  0.065133;0.605487;,
  0.065133;5.817032;,
  0.249522;-0.000000;,
  0.249522;1.000000;,
  0.000000;1.000000;,
  0.000000;-0.000000;,
  0.249522;-0.000000;,
  0.000000;-0.000000;,
  0.000000;1.000000;,
  0.249522;1.000000;,
  0.534668;-0.000000;,
  0.534668;1.000000;,
  0.534668;-0.000000;,
  0.534668;1.000000;,
  0.805371;-0.000000;,
  0.805371;1.000000;,
  1.000000;1.000000;,
  1.000000;-0.000000;,
  0.805371;-0.000000;,
  1.000000;-0.000000;,
  1.000000;1.000000;,
  0.805371;1.000000;,
  0.000000;-0.000000;,
  0.249522;-0.000000;,
  0.000000;1.000000;,
  0.534668;-0.000000;,
  0.249522;1.000000;,
  0.805371;-0.000000;,
  0.534668;1.000000;,
  1.000000;-0.000000;,
  0.805371;1.000000;,
  1.000000;1.000000;,
  0.000000;-0.000000;,
  0.249522;-0.000000;,
  0.000000;1.000000;,
  0.534668;-0.000000;,
  0.249522;1.000000;,
  0.805371;-0.000000;,
  0.534668;1.000000;,
  1.000000;-0.000000;,
  0.805371;1.000000;,
  1.000000;1.000000;;
 }
}
