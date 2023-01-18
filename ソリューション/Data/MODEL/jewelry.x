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
 68;
 0.00000;19.31377;0.00000;,
 1.33162;17.20590;-1.37637;,
 -0.03164;17.20590;-1.91483;,
 0.00000;19.31377;0.00000;,
 1.91484;17.20590;-0.03165;,
 0.00000;19.31377;0.00000;,
 1.37637;17.20590;1.33161;,
 0.00000;19.31377;0.00000;,
 0.03165;17.20590;1.91484;,
 0.00000;19.31377;0.00000;,
 -1.33161;17.20590;1.37637;,
 0.00000;19.31377;0.00000;,
 -1.91483;17.20590;0.03165;,
 0.00000;19.31377;0.00000;,
 -1.37636;17.20590;-1.33161;,
 0.00000;19.31377;0.00000;,
 -0.03164;17.20590;-1.91483;,
 0.00000;11.33813;0.00000;,
 1.38233;12.99995;0.01083;,
 0.96980;12.99995;0.98511;,
 0.00000;11.33813;0.00000;,
 -0.01083;12.99995;1.38233;,
 0.00000;11.33813;0.00000;,
 -0.98510;12.99995;0.96979;,
 0.00000;11.33813;0.00000;,
 -1.38231;12.99995;-0.01083;,
 0.00000;11.33813;0.00000;,
 -0.96979;12.99995;-0.98511;,
 0.00000;11.33813;0.00000;,
 0.01084;12.99995;-1.38232;,
 0.00000;11.33813;0.00000;,
 0.01084;12.99995;-1.38232;,
 0.98511;12.99995;-0.96979;,
 0.00000;11.33813;0.00000;,
 0.00000;19.73206;0.00000;,
 -0.65200;17.43568;-2.01302;,
 0.96238;17.43568;-1.88446;,
 0.00000;19.73206;0.00000;,
 2.01303;17.43568;-0.65201;,
 0.00000;19.73206;0.00000;,
 1.88446;17.43568;0.96238;,
 0.00000;19.73206;0.00000;,
 0.65201;17.43568;2.01302;,
 0.00000;19.73206;0.00000;,
 -0.96238;17.43568;1.88446;,
 0.00000;19.73206;0.00000;,
 -2.01302;17.43568;0.65201;,
 0.00000;19.73206;0.00000;,
 -1.88446;17.43568;-0.96238;,
 0.00000;19.73206;0.00000;,
 -0.65200;17.43568;-2.01302;,
 0.00000;10.91982;0.00000;,
 1.34293;12.75596;0.72760;,
 1.46409;12.75596;-0.43510;,
 0.00000;10.91982;0.00000;,
 0.43511;12.75596;1.46409;,
 0.00000;10.91982;0.00000;,
 -0.72760;12.75596;1.34293;,
 0.00000;10.91982;0.00000;,
 -1.46408;12.75596;0.43510;,
 0.00000;10.91982;0.00000;,
 -1.34292;12.75596;-0.72760;,
 0.00000;10.91982;0.00000;,
 -0.43510;12.75596;-1.46408;,
 0.00000;10.91982;0.00000;,
 0.72761;12.75596;-1.34292;,
 -0.43510;12.75596;-1.46408;,
 0.00000;10.91982;0.00000;;
 
 64;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 3;30,31,32;,
 3;33,32,18;,
 3;1,32,31;,
 3;1,31,2;,
 3;4,18,32;,
 3;4,32,1;,
 3;6,19,18;,
 3;6,18,4;,
 3;8,21,19;,
 3;8,19,6;,
 3;10,23,21;,
 3;10,21,8;,
 3;12,25,23;,
 3;12,23,10;,
 3;14,27,25;,
 3;14,25,12;,
 3;16,29,27;,
 3;16,27,14;,
 3;34,35,36;,
 3;37,36,38;,
 3;39,38,40;,
 3;41,40,42;,
 3;43,42,44;,
 3;45,44,46;,
 3;47,46,48;,
 3;49,48,50;,
 3;51,52,53;,
 3;54,55,52;,
 3;56,57,55;,
 3;58,59,57;,
 3;60,61,59;,
 3;62,63,61;,
 3;64,65,66;,
 3;67,53,65;,
 3;36,66,65;,
 3;36,35,66;,
 3;38,65,53;,
 3;38,36,65;,
 3;40,53,52;,
 3;40,38,53;,
 3;42,52,55;,
 3;42,40,52;,
 3;44,55,57;,
 3;44,42,55;,
 3;46,57,59;,
 3;46,44,57;,
 3;48,59,61;,
 3;48,46,59;,
 3;50,61,63;,
 3;50,48,61;;
 
 MeshMaterialList {
  2;
  64;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.448800;0.000000;0.800000;0.740000;;
   2.000000;
   0.550000;0.550000;0.550000;;
   0.044880;0.000000;0.080000;;
  }
  Material {
   0.737600;0.743200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  44;
  0.634907;0.721849;-0.275366;,
  -0.099254;0.218544;-0.970766;,
  0.616251;0.218544;-0.756619;,
  0.970766;0.218544;-0.099253;,
  0.756619;0.218545;0.616251;,
  0.099255;0.218545;0.970766;,
  -0.616253;0.218544;0.756618;,
  -0.970766;0.218544;0.099254;,
  -0.756619;0.218544;-0.616251;,
  0.086402;-0.347630;-0.933642;,
  0.721280;-0.347630;-0.599090;,
  0.933642;-0.347630;0.086403;,
  0.599090;-0.347630;0.721280;,
  -0.086404;-0.347631;0.933642;,
  -0.721282;-0.347630;0.599088;,
  -0.933642;-0.347630;-0.086402;,
  -0.599089;-0.347630;-0.721281;,
  0.271511;-0.690644;0.670293;,
  -0.254234;0.721850;0.643660;,
  -0.531936;0.672452;-0.514638;,
  -0.665957;-0.690643;-0.281983;,
  0.547857;-0.639505;-0.539339;,
  -0.522777;-0.726701;0.445657;,
  0.378607;-0.221823;0.898583;,
  -0.367676;-0.221824;0.903110;,
  -0.898582;-0.221824;0.378609;,
  -0.903110;-0.221824;-0.367677;,
  -0.378611;-0.221824;-0.898581;,
  0.367675;-0.221824;-0.903111;,
  0.898582;-0.221823;-0.378609;,
  0.903111;-0.221823;0.367676;,
  0.190378;0.347139;0.918287;,
  -0.514709;0.347139;0.783945;,
  -0.918287;0.347139;0.190378;,
  -0.783945;0.347139;-0.514708;,
  -0.190381;0.347139;-0.918286;,
  0.514710;0.347140;-0.783943;,
  0.918287;0.347139;-0.190378;,
  0.783945;0.347139;0.514709;,
  -0.455623;0.690644;-0.561621;,
  0.054532;-0.726702;-0.684786;,
  0.654938;-0.677631;0.334473;,
  0.719301;0.690643;0.074954;,
  -0.366232;0.639505;0.675950;;
  64;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;18,5,4;,
  3;18,6,5;,
  3;18,7,6;,
  3;19,8,7;,
  3;19,1,8;,
  3;17,11,12;,
  3;17,12,13;,
  3;17,13,14;,
  3;20,14,15;,
  3;20,15,16;,
  3;20,16,9;,
  3;21,9,10;,
  3;21,10,11;,
  3;2,10,9;,
  3;2,9,1;,
  3;3,11,10;,
  3;3,10,2;,
  3;4,12,11;,
  3;4,11,3;,
  3;5,13,12;,
  3;5,12,4;,
  3;6,14,13;,
  3;6,13,5;,
  3;7,15,14;,
  3;7,14,6;,
  3;8,16,15;,
  3;8,15,7;,
  3;1,9,16;,
  3;1,16,8;,
  3;22,23,24;,
  3;22,24,25;,
  3;22,25,26;,
  3;40,26,27;,
  3;40,27,28;,
  3;40,28,29;,
  3;41,29,30;,
  3;41,30,23;,
  3;39,34,33;,
  3;39,35,34;,
  3;39,36,35;,
  3;42,37,36;,
  3;42,38,37;,
  3;42,31,38;,
  3;43,32,31;,
  3;43,33,32;,
  3;24,31,32;,
  3;24,23,31;,
  3;25,32,33;,
  3;25,24,32;,
  3;26,33,34;,
  3;26,25,33;,
  3;27,34,35;,
  3;27,26,34;,
  3;28,35,36;,
  3;28,27,35;,
  3;29,36,37;,
  3;29,28,36;,
  3;30,37,38;,
  3;30,29,37;,
  3;23,38,31;,
  3;23,30,38;;
 }
 MeshTextureCoords {
  68;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.312500;1.000000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.437500;1.000000;,
  0.500000;0.500000;,
  0.562500;1.000000;,
  0.625000;0.500000;,
  0.687500;1.000000;,
  0.750000;0.500000;,
  0.812500;1.000000;,
  0.875000;0.500000;,
  0.937500;1.000000;,
  1.000000;0.500000;,
  0.062500;1.000000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.187500;1.000000;,
  0.062500;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.312500;1.000000;,
  0.375000;0.500000;,
  0.250000;0.500000;,
  0.437500;1.000000;,
  0.500000;0.500000;,
  0.562500;1.000000;,
  0.625000;0.500000;,
  0.687500;1.000000;,
  0.750000;0.500000;,
  0.812500;1.000000;,
  0.875000;0.500000;,
  0.937500;1.000000;,
  1.000000;0.500000;,
  0.062500;1.000000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.187500;1.000000;;
 }
}
