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
 176;
 -10.00000;150.00000;-10.00000;,
 10.00000;150.00000;-10.00000;,
 10.00000;124.99998;-10.00000;,
 -10.00000;124.99998;-10.00000;,
 30.00000;150.00000;-10.00000;,
 30.00000;124.99998;-10.00000;,
 50.00000;150.00000;-10.00000;,
 50.00000;124.99998;-10.00000;,
 69.99999;150.00000;-10.00000;,
 69.99999;124.99998;-10.00000;,
 90.00000;150.00000;-10.00000;,
 90.00000;124.99998;-10.00000;,
 110.00000;150.00000;-10.00000;,
 110.00000;124.99998;-10.00000;,
 10.00000;100.00003;-10.00000;,
 -10.00000;100.00003;-10.00000;,
 30.00000;100.00003;-10.00000;,
 50.00000;100.00003;-10.00000;,
 69.99999;100.00003;-10.00000;,
 90.00000;100.00003;-10.00000;,
 110.00000;100.00003;-10.00000;,
 10.00000;75.00000;-10.00000;,
 -10.00000;75.00000;-10.00000;,
 30.00000;75.00000;-10.00000;,
 50.00000;75.00000;-10.00000;,
 69.99999;75.00000;-10.00000;,
 90.00000;75.00000;-10.00000;,
 110.00000;75.00000;-10.00000;,
 10.00000;49.99998;-10.00000;,
 -10.00000;49.99998;-10.00000;,
 30.00000;49.99998;-10.00000;,
 50.00000;49.99998;-10.00000;,
 69.99999;49.99998;-10.00000;,
 90.00000;49.99998;-10.00000;,
 110.00000;49.99998;-10.00000;,
 10.00000;25.00003;-10.00000;,
 -10.00000;25.00003;-10.00000;,
 30.00000;25.00003;-10.00000;,
 50.00000;25.00003;-10.00000;,
 69.99999;25.00003;-10.00000;,
 90.00000;25.00003;-10.00000;,
 110.00000;25.00003;-10.00000;,
 10.00000;0.00000;-10.00000;,
 -10.00000;0.00000;-10.00000;,
 30.00000;0.00000;-10.00000;,
 50.00000;0.00000;-10.00000;,
 69.99999;0.00000;-10.00000;,
 90.00000;0.00000;-10.00000;,
 110.00000;0.00000;-10.00000;,
 110.00000;150.00000;-10.00000;,
 110.00000;150.00000;0.00000;,
 110.00000;124.99998;0.00000;,
 110.00000;124.99998;-10.00000;,
 110.00000;150.00000;10.00000;,
 110.00000;124.99998;10.00000;,
 110.00000;100.00003;0.00000;,
 110.00000;100.00003;-10.00000;,
 110.00000;100.00003;10.00000;,
 110.00000;75.00000;0.00000;,
 110.00000;75.00000;-10.00000;,
 110.00000;75.00000;10.00000;,
 110.00000;49.99998;0.00000;,
 110.00000;49.99998;-10.00000;,
 110.00000;49.99998;10.00000;,
 110.00000;25.00003;0.00000;,
 110.00000;25.00003;-10.00000;,
 110.00000;25.00003;10.00000;,
 110.00000;0.00000;0.00000;,
 110.00000;0.00000;-10.00000;,
 110.00000;0.00000;10.00000;,
 110.00000;150.00000;10.00000;,
 90.00000;150.00000;10.00000;,
 90.00000;124.99998;10.00000;,
 110.00000;124.99998;10.00000;,
 69.99999;150.00000;10.00000;,
 69.99999;124.99998;10.00000;,
 50.00000;150.00000;10.00000;,
 50.00000;124.99998;10.00000;,
 30.00000;150.00000;10.00000;,
 30.00000;124.99998;10.00000;,
 10.00000;150.00000;10.00000;,
 10.00000;124.99998;10.00000;,
 -10.00000;150.00000;10.00000;,
 -10.00000;124.99998;10.00000;,
 90.00000;100.00003;10.00000;,
 110.00000;100.00003;10.00000;,
 69.99999;100.00003;10.00000;,
 50.00000;100.00003;10.00000;,
 30.00000;100.00003;10.00000;,
 10.00000;100.00003;10.00000;,
 -10.00000;100.00003;10.00000;,
 90.00000;75.00000;10.00000;,
 110.00000;75.00000;10.00000;,
 69.99999;75.00000;10.00000;,
 50.00000;75.00000;10.00000;,
 30.00000;75.00000;10.00000;,
 10.00000;75.00000;10.00000;,
 -10.00000;75.00000;10.00000;,
 90.00000;49.99998;10.00000;,
 110.00000;49.99998;10.00000;,
 69.99999;49.99998;10.00000;,
 50.00000;49.99998;10.00000;,
 30.00000;49.99998;10.00000;,
 10.00000;49.99998;10.00000;,
 -10.00000;49.99998;10.00000;,
 90.00000;25.00003;10.00000;,
 110.00000;25.00003;10.00000;,
 69.99999;25.00003;10.00000;,
 50.00000;25.00003;10.00000;,
 30.00000;25.00003;10.00000;,
 10.00000;25.00003;10.00000;,
 -10.00000;25.00003;10.00000;,
 90.00000;0.00000;10.00000;,
 110.00000;0.00000;10.00000;,
 69.99999;0.00000;10.00000;,
 50.00000;0.00000;10.00000;,
 30.00000;0.00000;10.00000;,
 10.00000;0.00000;10.00000;,
 -10.00000;0.00000;10.00000;,
 -10.00000;150.00000;10.00000;,
 -10.00000;150.00000;0.00000;,
 -10.00000;124.99998;0.00000;,
 -10.00000;124.99998;10.00000;,
 -10.00000;150.00000;-10.00000;,
 -10.00000;124.99998;-10.00000;,
 -10.00000;100.00003;0.00000;,
 -10.00000;100.00003;10.00000;,
 -10.00000;100.00003;-10.00000;,
 -10.00000;75.00000;0.00000;,
 -10.00000;75.00000;10.00000;,
 -10.00000;75.00000;-10.00000;,
 -10.00000;49.99998;0.00000;,
 -10.00000;49.99998;10.00000;,
 -10.00000;49.99998;-10.00000;,
 -10.00000;25.00003;0.00000;,
 -10.00000;25.00003;10.00000;,
 -10.00000;25.00003;-10.00000;,
 -10.00000;0.00000;0.00000;,
 -10.00000;0.00000;10.00000;,
 -10.00000;0.00000;-10.00000;,
 10.00000;150.00000;10.00000;,
 10.00000;150.00000;0.00000;,
 -10.00000;150.00000;0.00000;,
 30.00000;150.00000;10.00000;,
 30.00000;150.00000;0.00000;,
 50.00000;150.00000;0.00000;,
 69.99999;150.00000;10.00000;,
 69.99999;150.00000;0.00000;,
 90.00000;150.00000;10.00000;,
 90.00000;150.00000;0.00000;,
 110.00000;150.00000;0.00000;,
 10.00000;150.00000;-10.00000;,
 -10.00000;150.00000;-10.00000;,
 30.00000;150.00000;-10.00000;,
 50.00000;150.00000;-10.00000;,
 69.99999;150.00000;-10.00000;,
 90.00000;150.00000;-10.00000;,
 110.00000;150.00000;-10.00000;,
 -10.00000;0.00000;0.00000;,
 10.00000;0.00000;0.00000;,
 10.00000;0.00000;10.00000;,
 30.00000;0.00000;0.00000;,
 30.00000;0.00000;10.00000;,
 50.00000;0.00000;0.00000;,
 69.99999;0.00000;0.00000;,
 69.99999;0.00000;10.00000;,
 90.00000;0.00000;0.00000;,
 90.00000;0.00000;10.00000;,
 110.00000;0.00000;0.00000;,
 -10.00000;0.00000;-10.00000;,
 10.00000;0.00000;-10.00000;,
 30.00000;0.00000;-10.00000;,
 50.00000;0.00000;-10.00000;,
 69.99999;0.00000;-10.00000;,
 90.00000;0.00000;-10.00000;,
 110.00000;0.00000;-10.00000;;
 
 120;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;3,2,14,15;,
 4;2,5,16,14;,
 4;5,7,17,16;,
 4;7,9,18,17;,
 4;9,11,19,18;,
 4;11,13,20,19;,
 4;15,14,21,22;,
 4;14,16,23,21;,
 4;16,17,24,23;,
 4;17,18,25,24;,
 4;18,19,26,25;,
 4;19,20,27,26;,
 4;22,21,28,29;,
 4;21,23,30,28;,
 4;23,24,31,30;,
 4;24,25,32,31;,
 4;25,26,33,32;,
 4;26,27,34,33;,
 4;29,28,35,36;,
 4;28,30,37,35;,
 4;30,31,38,37;,
 4;31,32,39,38;,
 4;32,33,40,39;,
 4;33,34,41,40;,
 4;36,35,42,43;,
 4;35,37,44,42;,
 4;37,38,45,44;,
 4;38,39,46,45;,
 4;39,40,47,46;,
 4;40,41,48,47;,
 4;49,50,51,52;,
 4;50,53,54,51;,
 4;52,51,55,56;,
 4;51,54,57,55;,
 4;56,55,58,59;,
 4;55,57,60,58;,
 4;59,58,61,62;,
 4;58,60,63,61;,
 4;62,61,64,65;,
 4;61,63,66,64;,
 4;65,64,67,68;,
 4;64,66,69,67;,
 4;70,71,72,73;,
 4;71,74,75,72;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;73,72,84,85;,
 4;72,75,86,84;,
 4;75,77,87,86;,
 4;77,79,88,87;,
 4;79,81,89,88;,
 4;81,83,90,89;,
 4;85,84,91,92;,
 4;84,86,93,91;,
 4;86,87,94,93;,
 4;87,88,95,94;,
 4;88,89,96,95;,
 4;89,90,97,96;,
 4;92,91,98,99;,
 4;91,93,100,98;,
 4;93,94,101,100;,
 4;94,95,102,101;,
 4;95,96,103,102;,
 4;96,97,104,103;,
 4;99,98,105,106;,
 4;98,100,107,105;,
 4;100,101,108,107;,
 4;101,102,109,108;,
 4;102,103,110,109;,
 4;103,104,111,110;,
 4;106,105,112,113;,
 4;105,107,114,112;,
 4;107,108,115,114;,
 4;108,109,116,115;,
 4;109,110,117,116;,
 4;110,111,118,117;,
 4;119,120,121,122;,
 4;120,123,124,121;,
 4;122,121,125,126;,
 4;121,124,127,125;,
 4;126,125,128,129;,
 4;125,127,130,128;,
 4;129,128,131,132;,
 4;128,130,133,131;,
 4;132,131,134,135;,
 4;131,133,136,134;,
 4;135,134,137,138;,
 4;134,136,139,137;,
 4;119,140,141,142;,
 4;140,143,144,141;,
 4;143,76,145,144;,
 4;76,146,147,145;,
 4;146,148,149,147;,
 4;148,53,150,149;,
 4;142,141,151,152;,
 4;141,144,153,151;,
 4;144,145,154,153;,
 4;145,147,155,154;,
 4;147,149,156,155;,
 4;149,150,157,156;,
 4;158,159,160,138;,
 4;159,161,162,160;,
 4;161,163,115,162;,
 4;163,164,165,115;,
 4;164,166,167,165;,
 4;166,168,69,167;,
 4;169,170,159,158;,
 4;170,171,161,159;,
 4;171,172,163,161;,
 4;172,173,164,163;,
 4;173,174,166,164;,
 4;174,175,168,166;;
 
 MeshMaterialList {
  1;
  120;
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
    "Data\\TEXTURE\\Concretewall3.jpg";
   }
  }
 }
 MeshNormals {
  6;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  120;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  176;
  0.000000;0.000000;,
  0.166667;0.000000;,
  0.166667;0.166667;,
  0.000000;0.166667;,
  0.333333;0.000000;,
  0.333333;0.166667;,
  0.500000;0.000000;,
  0.500000;0.166667;,
  0.666667;0.000000;,
  0.666667;0.166667;,
  0.833333;0.000000;,
  0.833333;0.166667;,
  1.000000;0.000000;,
  1.000000;0.166667;,
  0.166667;0.333333;,
  0.000000;0.333333;,
  0.333333;0.333333;,
  0.500000;0.333333;,
  0.666667;0.333333;,
  0.833333;0.333333;,
  1.000000;0.333333;,
  0.166667;0.500000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.500000;0.500000;,
  0.666667;0.500000;,
  0.833333;0.500000;,
  1.000000;0.500000;,
  0.166667;0.666667;,
  0.000000;0.666667;,
  0.333333;0.666667;,
  0.500000;0.666667;,
  0.666667;0.666667;,
  0.833333;0.666667;,
  1.000000;0.666667;,
  0.166667;0.833333;,
  0.000000;0.833333;,
  0.333333;0.833333;,
  0.500000;0.833333;,
  0.666667;0.833333;,
  0.833333;0.833333;,
  1.000000;0.833333;,
  0.166667;1.000000;,
  0.000000;1.000000;,
  0.333333;1.000000;,
  0.500000;1.000000;,
  0.666667;1.000000;,
  0.833333;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.166667;,
  0.000000;0.166667;,
  1.000000;0.000000;,
  1.000000;0.166667;,
  0.500000;0.333333;,
  0.000000;0.333333;,
  1.000000;0.333333;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.666667;,
  0.000000;0.666667;,
  1.000000;0.666667;,
  0.500000;0.833333;,
  0.000000;0.833333;,
  1.000000;0.833333;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166667;0.000000;,
  0.166667;0.166667;,
  0.000000;0.166667;,
  0.333333;0.000000;,
  0.333333;0.166667;,
  0.500000;0.000000;,
  0.500000;0.166667;,
  0.666667;0.000000;,
  0.666667;0.166667;,
  0.833333;0.000000;,
  0.833333;0.166667;,
  1.000000;0.000000;,
  1.000000;0.166667;,
  0.166667;0.333333;,
  0.000000;0.333333;,
  0.333333;0.333333;,
  0.500000;0.333333;,
  0.666667;0.333333;,
  0.833333;0.333333;,
  1.000000;0.333333;,
  0.166667;0.500000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.500000;0.500000;,
  0.666667;0.500000;,
  0.833333;0.500000;,
  1.000000;0.500000;,
  0.166667;0.666667;,
  0.000000;0.666667;,
  0.333333;0.666667;,
  0.500000;0.666667;,
  0.666667;0.666667;,
  0.833333;0.666667;,
  1.000000;0.666667;,
  0.166667;0.833333;,
  0.000000;0.833333;,
  0.333333;0.833333;,
  0.500000;0.833333;,
  0.666667;0.833333;,
  0.833333;0.833333;,
  1.000000;0.833333;,
  0.166667;1.000000;,
  0.000000;1.000000;,
  0.333333;1.000000;,
  0.500000;1.000000;,
  0.666667;1.000000;,
  0.833333;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.166667;,
  0.000000;0.166667;,
  1.000000;0.000000;,
  1.000000;0.166667;,
  0.500000;0.333333;,
  0.000000;0.333333;,
  1.000000;0.333333;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.666667;,
  0.000000;0.666667;,
  1.000000;0.666667;,
  0.500000;0.833333;,
  0.000000;0.833333;,
  1.000000;0.833333;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.166667;0.000000;,
  0.166667;0.500000;,
  0.000000;0.500000;,
  0.333333;0.000000;,
  0.333333;0.500000;,
  0.500000;0.500000;,
  0.666667;0.000000;,
  0.666667;0.500000;,
  0.833333;0.000000;,
  0.833333;0.500000;,
  1.000000;0.500000;,
  0.166667;1.000000;,
  0.000000;1.000000;,
  0.333333;1.000000;,
  0.500000;1.000000;,
  0.666667;1.000000;,
  0.833333;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.166667;0.500000;,
  0.166667;1.000000;,
  0.333333;0.500000;,
  0.333333;1.000000;,
  0.500000;0.500000;,
  0.666667;0.500000;,
  0.666667;1.000000;,
  0.833333;0.500000;,
  0.833333;1.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.166667;0.000000;,
  0.333333;0.000000;,
  0.500000;0.000000;,
  0.666667;0.000000;,
  0.833333;0.000000;,
  1.000000;0.000000;;
 }
}
