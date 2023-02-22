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
 330;
 -10.00000;150.00000;-10.00000;,
 2.00000;150.00000;-10.00000;,
 2.00000;135.00000;-10.00000;,
 -10.00000;135.00000;-10.00000;,
 14.00000;150.00000;-10.00000;,
 14.00000;135.00000;-10.00000;,
 26.00000;150.00000;-10.00000;,
 26.00000;135.00000;-10.00000;,
 38.00000;150.00000;-10.00000;,
 38.00000;135.00000;-10.00000;,
 50.00000;150.00000;-10.00000;,
 50.00000;135.00000;-10.00000;,
 62.00000;150.00000;-10.00000;,
 62.00000;135.00000;-10.00000;,
 74.00000;150.00000;-10.00000;,
 74.00000;135.00000;-10.00000;,
 86.00000;150.00000;-10.00000;,
 86.00000;135.00000;-10.00000;,
 98.00000;150.00000;-10.00000;,
 98.00000;135.00000;-10.00000;,
 110.00000;150.00000;-10.00000;,
 110.00000;135.00000;-10.00000;,
 2.00000;120.00000;-10.00000;,
 -10.00000;120.00000;-10.00000;,
 14.00000;120.00000;-10.00000;,
 26.00000;120.00000;-10.00000;,
 38.00000;120.00000;-10.00000;,
 50.00000;120.00000;-10.00000;,
 62.00000;120.00000;-10.00000;,
 74.00000;120.00000;-10.00000;,
 86.00000;120.00000;-10.00000;,
 98.00000;120.00000;-10.00000;,
 110.00000;120.00000;-10.00000;,
 2.00000;105.00000;-10.00000;,
 -10.00000;105.00000;-10.00000;,
 14.00000;105.00000;-10.00000;,
 26.00000;105.00000;-10.00000;,
 38.00000;105.00000;-10.00000;,
 50.00000;105.00000;-10.00000;,
 62.00000;105.00000;-10.00000;,
 74.00000;105.00000;-10.00000;,
 86.00000;105.00000;-10.00000;,
 98.00000;105.00000;-10.00000;,
 110.00000;105.00000;-10.00000;,
 2.00000;90.00000;-10.00000;,
 -10.00000;90.00000;-10.00000;,
 14.00000;90.00000;-10.00000;,
 26.00000;90.00000;-10.00000;,
 38.00000;90.00000;-10.00000;,
 50.00000;90.00000;-10.00000;,
 62.00000;90.00000;-10.00000;,
 74.00000;90.00000;-10.00000;,
 86.00000;90.00000;-10.00000;,
 98.00000;90.00000;-10.00000;,
 110.00000;90.00000;-10.00000;,
 2.00000;75.00000;-10.00000;,
 -10.00000;75.00000;-10.00000;,
 14.00000;75.00000;-10.00000;,
 26.00000;75.00000;-10.00000;,
 38.00000;75.00000;-10.00000;,
 50.00000;75.00000;-10.00000;,
 62.00000;75.00000;-10.00000;,
 74.00000;75.00000;-10.00000;,
 86.00000;75.00000;-10.00000;,
 98.00000;75.00000;-10.00000;,
 110.00000;75.00000;-10.00000;,
 2.00000;60.00000;-10.00000;,
 -10.00000;60.00000;-10.00000;,
 14.00000;60.00000;-10.00000;,
 26.00000;60.00000;-10.00000;,
 38.00000;60.00000;-10.00000;,
 50.00000;60.00000;-10.00000;,
 62.00000;60.00000;-10.00000;,
 74.00000;60.00000;-10.00000;,
 86.00000;60.00000;-10.00000;,
 98.00000;60.00000;-10.00000;,
 110.00000;60.00000;-10.00000;,
 2.00000;45.00000;-10.00000;,
 -10.00000;45.00000;-10.00000;,
 14.00000;45.00000;-10.00000;,
 26.00000;45.00000;-10.00000;,
 38.00000;45.00000;-10.00000;,
 50.00000;45.00000;-10.00000;,
 62.00000;45.00000;-10.00000;,
 74.00000;45.00000;-10.00000;,
 86.00000;45.00000;-10.00000;,
 98.00000;45.00000;-10.00000;,
 110.00000;45.00000;-10.00000;,
 2.00000;30.00000;-10.00000;,
 -10.00000;30.00000;-10.00000;,
 14.00000;30.00000;-10.00000;,
 26.00000;30.00000;-10.00000;,
 38.00000;30.00000;-10.00000;,
 50.00000;30.00000;-10.00000;,
 62.00000;30.00000;-10.00000;,
 74.00000;30.00000;-10.00000;,
 86.00000;30.00000;-10.00000;,
 98.00000;30.00000;-10.00000;,
 110.00000;30.00000;-10.00000;,
 2.00000;15.00000;-10.00000;,
 -10.00000;15.00000;-10.00000;,
 14.00000;15.00000;-10.00000;,
 26.00000;15.00000;-10.00000;,
 38.00000;15.00000;-10.00000;,
 50.00000;15.00000;-10.00000;,
 62.00000;15.00000;-10.00000;,
 74.00000;15.00000;-10.00000;,
 86.00000;15.00000;-10.00000;,
 98.00000;15.00000;-10.00000;,
 110.00000;15.00000;-10.00000;,
 2.00000;0.00000;-10.00000;,
 -10.00000;0.00000;-10.00000;,
 14.00000;0.00000;-10.00000;,
 26.00000;0.00000;-10.00000;,
 38.00000;0.00000;-10.00000;,
 50.00000;0.00000;-10.00000;,
 62.00000;0.00000;-10.00000;,
 74.00000;0.00000;-10.00000;,
 86.00000;0.00000;-10.00000;,
 98.00000;0.00000;-10.00000;,
 110.00000;0.00000;-10.00000;,
 110.00000;150.00000;0.00000;,
 110.00000;135.00000;0.00000;,
 110.00000;150.00000;10.00000;,
 110.00000;135.00000;10.00000;,
 110.00000;120.00000;0.00000;,
 110.00000;120.00000;10.00000;,
 110.00000;105.00000;0.00000;,
 110.00000;105.00000;10.00000;,
 110.00000;90.00000;0.00000;,
 110.00000;90.00000;10.00000;,
 110.00000;75.00000;0.00000;,
 110.00000;75.00000;10.00000;,
 110.00000;60.00000;0.00000;,
 110.00000;60.00000;10.00000;,
 110.00000;45.00000;0.00000;,
 110.00000;45.00000;10.00000;,
 110.00000;30.00000;0.00000;,
 110.00000;30.00000;10.00000;,
 110.00000;15.00000;0.00000;,
 110.00000;15.00000;10.00000;,
 110.00000;0.00000;0.00000;,
 110.00000;0.00000;10.00000;,
 98.00000;150.00000;10.00000;,
 98.00000;135.00000;10.00000;,
 86.00000;150.00000;10.00000;,
 86.00000;135.00000;10.00000;,
 74.00000;150.00000;10.00000;,
 74.00000;135.00000;10.00000;,
 62.00000;150.00000;10.00000;,
 62.00000;135.00000;10.00000;,
 50.00000;150.00000;10.00000;,
 50.00000;135.00000;10.00000;,
 38.00000;150.00000;10.00000;,
 38.00000;135.00000;10.00000;,
 26.00000;150.00000;10.00000;,
 26.00000;135.00000;10.00000;,
 14.00000;150.00000;10.00000;,
 14.00000;135.00000;10.00000;,
 2.00000;150.00000;10.00000;,
 2.00000;135.00000;10.00000;,
 -10.00000;150.00000;10.00000;,
 -10.00000;135.00000;10.00000;,
 98.00000;120.00000;10.00000;,
 86.00000;120.00000;10.00000;,
 74.00000;120.00000;10.00000;,
 62.00000;120.00000;10.00000;,
 50.00000;120.00000;10.00000;,
 38.00000;120.00000;10.00000;,
 26.00000;120.00000;10.00000;,
 14.00000;120.00000;10.00000;,
 2.00000;120.00000;10.00000;,
 -10.00000;120.00000;10.00000;,
 98.00000;105.00000;10.00000;,
 86.00000;105.00000;10.00000;,
 74.00000;105.00000;10.00000;,
 62.00000;105.00000;10.00000;,
 50.00000;105.00000;10.00000;,
 38.00000;105.00000;10.00000;,
 26.00000;105.00000;10.00000;,
 14.00000;105.00000;10.00000;,
 2.00000;105.00000;10.00000;,
 -10.00000;105.00000;10.00000;,
 98.00000;90.00000;10.00000;,
 86.00000;90.00000;10.00000;,
 74.00000;90.00000;10.00000;,
 62.00000;90.00000;10.00000;,
 50.00000;90.00000;10.00000;,
 38.00000;90.00000;10.00000;,
 26.00000;90.00000;10.00000;,
 14.00000;90.00000;10.00000;,
 2.00000;90.00000;10.00000;,
 -10.00000;90.00000;10.00000;,
 98.00000;75.00000;10.00000;,
 86.00000;75.00000;10.00000;,
 74.00000;75.00000;10.00000;,
 62.00000;75.00000;10.00000;,
 50.00000;75.00000;10.00000;,
 38.00000;75.00000;10.00000;,
 26.00000;75.00000;10.00000;,
 14.00000;75.00000;10.00000;,
 2.00000;75.00000;10.00000;,
 -10.00000;75.00000;10.00000;,
 98.00000;60.00000;10.00000;,
 86.00000;60.00000;10.00000;,
 74.00000;60.00000;10.00000;,
 62.00000;60.00000;10.00000;,
 50.00000;60.00000;10.00000;,
 38.00000;60.00000;10.00000;,
 26.00000;60.00000;10.00000;,
 14.00000;60.00000;10.00000;,
 2.00000;60.00000;10.00000;,
 -10.00000;60.00000;10.00000;,
 98.00000;45.00000;10.00000;,
 86.00000;45.00000;10.00000;,
 74.00000;45.00000;10.00000;,
 62.00000;45.00000;10.00000;,
 50.00000;45.00000;10.00000;,
 38.00000;45.00000;10.00000;,
 26.00000;45.00000;10.00000;,
 14.00000;45.00000;10.00000;,
 2.00000;45.00000;10.00000;,
 -10.00000;45.00000;10.00000;,
 98.00000;30.00000;10.00000;,
 86.00000;30.00000;10.00000;,
 74.00000;30.00000;10.00000;,
 62.00000;30.00000;10.00000;,
 50.00000;30.00000;10.00000;,
 38.00000;30.00000;10.00000;,
 26.00000;30.00000;10.00000;,
 14.00000;30.00000;10.00000;,
 2.00000;30.00000;10.00000;,
 -10.00000;30.00000;10.00000;,
 98.00000;15.00000;10.00000;,
 86.00000;15.00000;10.00000;,
 74.00000;15.00000;10.00000;,
 62.00000;15.00000;10.00000;,
 50.00000;15.00000;10.00000;,
 38.00000;15.00000;10.00000;,
 26.00000;15.00000;10.00000;,
 14.00000;15.00000;10.00000;,
 2.00000;15.00000;10.00000;,
 -10.00000;15.00000;10.00000;,
 98.00000;0.00000;10.00000;,
 86.00000;0.00000;10.00000;,
 74.00000;0.00000;10.00000;,
 62.00000;0.00000;10.00000;,
 50.00000;0.00000;10.00000;,
 38.00000;0.00000;10.00000;,
 26.00000;0.00000;10.00000;,
 14.00000;0.00000;10.00000;,
 2.00000;0.00000;10.00000;,
 -10.00000;0.00000;10.00000;,
 -10.00000;150.00000;0.00000;,
 -10.00000;135.00000;0.00000;,
 -10.00000;120.00000;0.00000;,
 -10.00000;105.00000;0.00000;,
 -10.00000;90.00000;0.00000;,
 -10.00000;75.00000;0.00000;,
 -10.00000;60.00000;0.00000;,
 -10.00000;45.00000;0.00000;,
 -10.00000;30.00000;0.00000;,
 -10.00000;15.00000;0.00000;,
 -10.00000;0.00000;0.00000;,
 -10.00000;150.00000;10.00000;,
 2.00000;150.00000;10.00000;,
 2.00000;150.00000;0.00000;,
 -10.00000;150.00000;0.00000;,
 14.00000;150.00000;10.00000;,
 14.00000;150.00000;0.00000;,
 26.00000;150.00000;10.00000;,
 26.00000;150.00000;0.00000;,
 38.00000;150.00000;10.00000;,
 38.00000;150.00000;0.00000;,
 50.00000;150.00000;10.00000;,
 50.00000;150.00000;0.00000;,
 62.00000;150.00000;10.00000;,
 62.00000;150.00000;0.00000;,
 74.00000;150.00000;10.00000;,
 74.00000;150.00000;0.00000;,
 86.00000;150.00000;10.00000;,
 86.00000;150.00000;0.00000;,
 98.00000;150.00000;10.00000;,
 98.00000;150.00000;0.00000;,
 110.00000;150.00000;10.00000;,
 110.00000;150.00000;0.00000;,
 2.00000;150.00000;-10.00000;,
 -10.00000;150.00000;-10.00000;,
 14.00000;150.00000;-10.00000;,
 26.00000;150.00000;-10.00000;,
 38.00000;150.00000;-10.00000;,
 50.00000;150.00000;-10.00000;,
 62.00000;150.00000;-10.00000;,
 74.00000;150.00000;-10.00000;,
 86.00000;150.00000;-10.00000;,
 98.00000;150.00000;-10.00000;,
 110.00000;150.00000;-10.00000;,
 -10.00000;0.00000;0.00000;,
 2.00000;0.00000;0.00000;,
 2.00000;0.00000;10.00000;,
 -10.00000;0.00000;10.00000;,
 14.00000;0.00000;0.00000;,
 14.00000;0.00000;10.00000;,
 26.00000;0.00000;0.00000;,
 26.00000;0.00000;10.00000;,
 38.00000;0.00000;0.00000;,
 38.00000;0.00000;10.00000;,
 50.00000;0.00000;0.00000;,
 50.00000;0.00000;10.00000;,
 62.00000;0.00000;0.00000;,
 62.00000;0.00000;10.00000;,
 74.00000;0.00000;0.00000;,
 74.00000;0.00000;10.00000;,
 86.00000;0.00000;0.00000;,
 86.00000;0.00000;10.00000;,
 98.00000;0.00000;0.00000;,
 98.00000;0.00000;10.00000;,
 110.00000;0.00000;0.00000;,
 110.00000;0.00000;10.00000;,
 -10.00000;0.00000;-10.00000;,
 2.00000;0.00000;-10.00000;,
 14.00000;0.00000;-10.00000;,
 26.00000;0.00000;-10.00000;,
 38.00000;0.00000;-10.00000;,
 50.00000;0.00000;-10.00000;,
 62.00000;0.00000;-10.00000;,
 74.00000;0.00000;-10.00000;,
 86.00000;0.00000;-10.00000;,
 98.00000;0.00000;-10.00000;,
 110.00000;0.00000;-10.00000;;
 
 280;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;3,2,22,23;,
 4;2,5,24,22;,
 4;5,7,25,24;,
 4;7,9,26,25;,
 4;9,11,27,26;,
 4;11,13,28,27;,
 4;13,15,29,28;,
 4;15,17,30,29;,
 4;17,19,31,30;,
 4;19,21,32,31;,
 4;23,22,33,34;,
 4;22,24,35,33;,
 4;24,25,36,35;,
 4;25,26,37,36;,
 4;26,27,38,37;,
 4;27,28,39,38;,
 4;28,29,40,39;,
 4;29,30,41,40;,
 4;30,31,42,41;,
 4;31,32,43,42;,
 4;34,33,44,45;,
 4;33,35,46,44;,
 4;35,36,47,46;,
 4;36,37,48,47;,
 4;37,38,49,48;,
 4;38,39,50,49;,
 4;39,40,51,50;,
 4;40,41,52,51;,
 4;41,42,53,52;,
 4;42,43,54,53;,
 4;45,44,55,56;,
 4;44,46,57,55;,
 4;46,47,58,57;,
 4;47,48,59,58;,
 4;48,49,60,59;,
 4;49,50,61,60;,
 4;50,51,62,61;,
 4;51,52,63,62;,
 4;52,53,64,63;,
 4;53,54,65,64;,
 4;56,55,66,67;,
 4;55,57,68,66;,
 4;57,58,69,68;,
 4;58,59,70,69;,
 4;59,60,71,70;,
 4;60,61,72,71;,
 4;61,62,73,72;,
 4;62,63,74,73;,
 4;63,64,75,74;,
 4;64,65,76,75;,
 4;67,66,77,78;,
 4;66,68,79,77;,
 4;68,69,80,79;,
 4;69,70,81,80;,
 4;70,71,82,81;,
 4;71,72,83,82;,
 4;72,73,84,83;,
 4;73,74,85,84;,
 4;74,75,86,85;,
 4;75,76,87,86;,
 4;78,77,88,89;,
 4;77,79,90,88;,
 4;79,80,91,90;,
 4;80,81,92,91;,
 4;81,82,93,92;,
 4;82,83,94,93;,
 4;83,84,95,94;,
 4;84,85,96,95;,
 4;85,86,97,96;,
 4;86,87,98,97;,
 4;89,88,99,100;,
 4;88,90,101,99;,
 4;90,91,102,101;,
 4;91,92,103,102;,
 4;92,93,104,103;,
 4;93,94,105,104;,
 4;94,95,106,105;,
 4;95,96,107,106;,
 4;96,97,108,107;,
 4;97,98,109,108;,
 4;100,99,110,111;,
 4;99,101,112,110;,
 4;101,102,113,112;,
 4;102,103,114,113;,
 4;103,104,115,114;,
 4;104,105,116,115;,
 4;105,106,117,116;,
 4;106,107,118,117;,
 4;107,108,119,118;,
 4;108,109,120,119;,
 4;20,121,122,21;,
 4;121,123,124,122;,
 4;21,122,125,32;,
 4;122,124,126,125;,
 4;32,125,127,43;,
 4;125,126,128,127;,
 4;43,127,129,54;,
 4;127,128,130,129;,
 4;54,129,131,65;,
 4;129,130,132,131;,
 4;65,131,133,76;,
 4;131,132,134,133;,
 4;76,133,135,87;,
 4;133,134,136,135;,
 4;87,135,137,98;,
 4;135,136,138,137;,
 4;98,137,139,109;,
 4;137,138,140,139;,
 4;109,139,141,120;,
 4;139,140,142,141;,
 4;123,143,144,124;,
 4;143,145,146,144;,
 4;145,147,148,146;,
 4;147,149,150,148;,
 4;149,151,152,150;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 4;155,157,158,156;,
 4;157,159,160,158;,
 4;159,161,162,160;,
 4;124,144,163,126;,
 4;144,146,164,163;,
 4;146,148,165,164;,
 4;148,150,166,165;,
 4;150,152,167,166;,
 4;152,154,168,167;,
 4;154,156,169,168;,
 4;156,158,170,169;,
 4;158,160,171,170;,
 4;160,162,172,171;,
 4;126,163,173,128;,
 4;163,164,174,173;,
 4;164,165,175,174;,
 4;165,166,176,175;,
 4;166,167,177,176;,
 4;167,168,178,177;,
 4;168,169,179,178;,
 4;169,170,180,179;,
 4;170,171,181,180;,
 4;171,172,182,181;,
 4;128,173,183,130;,
 4;173,174,184,183;,
 4;174,175,185,184;,
 4;175,176,186,185;,
 4;176,177,187,186;,
 4;177,178,188,187;,
 4;178,179,189,188;,
 4;179,180,190,189;,
 4;180,181,191,190;,
 4;181,182,192,191;,
 4;130,183,193,132;,
 4;183,184,194,193;,
 4;184,185,195,194;,
 4;185,186,196,195;,
 4;186,187,197,196;,
 4;187,188,198,197;,
 4;188,189,199,198;,
 4;189,190,200,199;,
 4;190,191,201,200;,
 4;191,192,202,201;,
 4;132,193,203,134;,
 4;193,194,204,203;,
 4;194,195,205,204;,
 4;195,196,206,205;,
 4;196,197,207,206;,
 4;197,198,208,207;,
 4;198,199,209,208;,
 4;199,200,210,209;,
 4;200,201,211,210;,
 4;201,202,212,211;,
 4;134,203,213,136;,
 4;203,204,214,213;,
 4;204,205,215,214;,
 4;205,206,216,215;,
 4;206,207,217,216;,
 4;207,208,218,217;,
 4;208,209,219,218;,
 4;209,210,220,219;,
 4;210,211,221,220;,
 4;211,212,222,221;,
 4;136,213,223,138;,
 4;213,214,224,223;,
 4;214,215,225,224;,
 4;215,216,226,225;,
 4;216,217,227,226;,
 4;217,218,228,227;,
 4;218,219,229,228;,
 4;219,220,230,229;,
 4;220,221,231,230;,
 4;221,222,232,231;,
 4;138,223,233,140;,
 4;223,224,234,233;,
 4;224,225,235,234;,
 4;225,226,236,235;,
 4;226,227,237,236;,
 4;227,228,238,237;,
 4;228,229,239,238;,
 4;229,230,240,239;,
 4;230,231,241,240;,
 4;231,232,242,241;,
 4;140,233,243,142;,
 4;233,234,244,243;,
 4;234,235,245,244;,
 4;235,236,246,245;,
 4;236,237,247,246;,
 4;237,238,248,247;,
 4;238,239,249,248;,
 4;239,240,250,249;,
 4;240,241,251,250;,
 4;241,242,252,251;,
 4;161,253,254,162;,
 4;253,0,3,254;,
 4;162,254,255,172;,
 4;254,3,23,255;,
 4;172,255,256,182;,
 4;255,23,34,256;,
 4;182,256,257,192;,
 4;256,34,45,257;,
 4;192,257,258,202;,
 4;257,45,56,258;,
 4;202,258,259,212;,
 4;258,56,67,259;,
 4;212,259,260,222;,
 4;259,67,78,260;,
 4;222,260,261,232;,
 4;260,78,89,261;,
 4;232,261,262,242;,
 4;261,89,100,262;,
 4;242,262,263,252;,
 4;262,100,111,263;,
 4;264,265,266,267;,
 4;265,268,269,266;,
 4;268,270,271,269;,
 4;270,272,273,271;,
 4;272,274,275,273;,
 4;274,276,277,275;,
 4;276,278,279,277;,
 4;278,280,281,279;,
 4;280,282,283,281;,
 4;282,284,285,283;,
 4;267,266,286,287;,
 4;266,269,288,286;,
 4;269,271,289,288;,
 4;271,273,290,289;,
 4;273,275,291,290;,
 4;275,277,292,291;,
 4;277,279,293,292;,
 4;279,281,294,293;,
 4;281,283,295,294;,
 4;283,285,296,295;,
 4;297,298,299,300;,
 4;298,301,302,299;,
 4;301,303,304,302;,
 4;303,305,306,304;,
 4;305,307,308,306;,
 4;307,309,310,308;,
 4;309,311,312,310;,
 4;311,313,314,312;,
 4;313,315,316,314;,
 4;315,317,318,316;,
 4;319,320,298,297;,
 4;320,321,301,298;,
 4;321,322,303,301;,
 4;322,323,305,303;,
 4;323,324,307,305;,
 4;324,325,309,307;,
 4;325,326,311,309;,
 4;326,327,313,311;,
 4;327,328,315,313;,
 4;328,329,317,315;;
 
 MeshMaterialList {
  2;
  280;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data\\TEXTURE\\tile.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
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
  280;
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
  330;
  1.739349;1.739350;,
  1.491479;1.739350;,
  1.491479;1.491480;,
  1.739349;1.491480;,
  1.243609;1.739350;,
  1.243609;1.491480;,
  0.995740;1.739350;,
  0.995740;1.491480;,
  0.747870;1.739350;,
  0.747870;1.491480;,
  0.500000;1.739350;,
  0.500000;1.491480;,
  0.252130;1.739350;,
  0.252130;1.491480;,
  0.004260;1.739350;,
  0.004260;1.491480;,
  -0.243609;1.739350;,
  -0.243609;1.491480;,
  -0.491479;1.739350;,
  -0.491479;1.491480;,
  -0.739349;1.739350;,
  -0.739349;1.491480;,
  1.491479;1.243610;,
  1.739349;1.243610;,
  1.243609;1.243610;,
  0.995740;1.243610;,
  0.747870;1.243610;,
  0.500000;1.243610;,
  0.252130;1.243610;,
  0.004260;1.243610;,
  -0.243609;1.243610;,
  -0.491479;1.243610;,
  -0.739349;1.243610;,
  1.491479;0.995740;,
  1.739349;0.995740;,
  1.243609;0.995740;,
  0.995740;0.995740;,
  0.747870;0.995740;,
  0.500000;0.995740;,
  0.252130;0.995740;,
  0.004260;0.995740;,
  -0.243609;0.995740;,
  -0.491479;0.995740;,
  -0.739349;0.995740;,
  1.491479;0.747870;,
  1.739349;0.747870;,
  1.243609;0.747870;,
  0.995740;0.747870;,
  0.747870;0.747870;,
  0.500000;0.747870;,
  0.252130;0.747870;,
  0.004260;0.747870;,
  -0.243609;0.747870;,
  -0.491479;0.747870;,
  -0.739349;0.747870;,
  1.491479;0.500000;,
  1.739349;0.500000;,
  1.243609;0.500000;,
  0.995740;0.500000;,
  0.747870;0.500000;,
  0.500000;0.500000;,
  0.252130;0.500000;,
  0.004260;0.500000;,
  -0.243609;0.500000;,
  -0.491479;0.500000;,
  -0.739349;0.500000;,
  1.491479;0.252130;,
  1.739349;0.252130;,
  1.243609;0.252130;,
  0.995740;0.252130;,
  0.747870;0.252130;,
  0.500000;0.252130;,
  0.252130;0.252130;,
  0.004260;0.252130;,
  -0.243609;0.252130;,
  -0.491479;0.252130;,
  -0.739349;0.252130;,
  1.491479;0.004260;,
  1.739349;0.004260;,
  1.243609;0.004260;,
  0.995740;0.004260;,
  0.747870;0.004260;,
  0.500000;0.004260;,
  0.252130;0.004260;,
  0.004260;0.004260;,
  -0.243609;0.004260;,
  -0.491479;0.004260;,
  -0.739349;0.004260;,
  1.491479;-0.243610;,
  1.739349;-0.243610;,
  1.243609;-0.243610;,
  0.995740;-0.243610;,
  0.747870;-0.243610;,
  0.500000;-0.243610;,
  0.252130;-0.243610;,
  0.004260;-0.243610;,
  -0.243609;-0.243610;,
  -0.491479;-0.243610;,
  -0.739349;-0.243610;,
  1.491479;-0.491480;,
  1.739349;-0.491480;,
  1.243609;-0.491480;,
  0.995740;-0.491480;,
  0.747870;-0.491480;,
  0.500000;-0.491480;,
  0.252130;-0.491480;,
  0.004260;-0.491480;,
  -0.243609;-0.491480;,
  -0.491479;-0.491480;,
  -0.739349;-0.491480;,
  1.491479;-0.739350;,
  1.739349;-0.739350;,
  1.243609;-0.739350;,
  0.995740;-0.739350;,
  0.747870;-0.739350;,
  0.500000;-0.739350;,
  0.252130;-0.739350;,
  0.004260;-0.739350;,
  -0.243609;-0.739350;,
  -0.491479;-0.739350;,
  -0.739349;-0.739350;,
  -0.739349;1.739350;,
  -0.739349;1.491480;,
  -0.739349;1.739350;,
  -0.739349;1.491480;,
  -0.739349;1.243610;,
  -0.739349;1.243610;,
  -0.739349;0.995740;,
  -0.739349;0.995740;,
  -0.739349;0.747870;,
  -0.739349;0.747870;,
  -0.739349;0.500000;,
  -0.739349;0.500000;,
  -0.739349;0.252130;,
  -0.739349;0.252130;,
  -0.739349;0.004260;,
  -0.739349;0.004260;,
  -0.739349;-0.243610;,
  -0.739349;-0.243610;,
  -0.739349;-0.491480;,
  -0.739349;-0.491480;,
  -0.739349;-0.739350;,
  -0.739349;-0.739350;,
  -0.491479;1.739350;,
  -0.491479;1.491480;,
  -0.243609;1.739350;,
  -0.243609;1.491480;,
  0.004260;1.739350;,
  0.004260;1.491480;,
  0.252130;1.739350;,
  0.252130;1.491480;,
  0.500000;1.739350;,
  0.500000;1.491480;,
  0.747870;1.739350;,
  0.747870;1.491480;,
  0.995740;1.739350;,
  0.995740;1.491480;,
  1.243609;1.739350;,
  1.243609;1.491480;,
  1.491479;1.739350;,
  1.491479;1.491480;,
  1.739349;1.739350;,
  1.739349;1.491480;,
  -0.491479;1.243610;,
  -0.243609;1.243610;,
  0.004260;1.243610;,
  0.252130;1.243610;,
  0.500000;1.243610;,
  0.747870;1.243610;,
  0.995740;1.243610;,
  1.243609;1.243610;,
  1.491479;1.243610;,
  1.739349;1.243610;,
  -0.491479;0.995740;,
  -0.243609;0.995740;,
  0.004260;0.995740;,
  0.252130;0.995740;,
  0.500000;0.995740;,
  0.747870;0.995740;,
  0.995740;0.995740;,
  1.243609;0.995740;,
  1.491479;0.995740;,
  1.739349;0.995740;,
  -0.491479;0.747870;,
  -0.243609;0.747870;,
  0.004260;0.747870;,
  0.252130;0.747870;,
  0.500000;0.747870;,
  0.747870;0.747870;,
  0.995740;0.747870;,
  1.243609;0.747870;,
  1.491479;0.747870;,
  1.739349;0.747870;,
  -0.491479;0.500000;,
  -0.243609;0.500000;,
  0.004260;0.500000;,
  0.252130;0.500000;,
  0.500000;0.500000;,
  0.747870;0.500000;,
  0.995740;0.500000;,
  1.243609;0.500000;,
  1.491479;0.500000;,
  1.739349;0.500000;,
  -0.491479;0.252130;,
  -0.243609;0.252130;,
  0.004260;0.252130;,
  0.252130;0.252130;,
  0.500000;0.252130;,
  0.747870;0.252130;,
  0.995740;0.252130;,
  1.243609;0.252130;,
  1.491479;0.252130;,
  1.739349;0.252130;,
  -0.491479;0.004260;,
  -0.243609;0.004260;,
  0.004260;0.004260;,
  0.252130;0.004260;,
  0.500000;0.004260;,
  0.747870;0.004260;,
  0.995740;0.004260;,
  1.243609;0.004260;,
  1.491479;0.004260;,
  1.739349;0.004260;,
  -0.491479;-0.243610;,
  -0.243609;-0.243610;,
  0.004260;-0.243610;,
  0.252130;-0.243610;,
  0.500000;-0.243610;,
  0.747870;-0.243610;,
  0.995740;-0.243610;,
  1.243609;-0.243610;,
  1.491479;-0.243610;,
  1.739349;-0.243610;,
  -0.491479;-0.491480;,
  -0.243609;-0.491480;,
  0.004260;-0.491480;,
  0.252130;-0.491480;,
  0.500000;-0.491480;,
  0.747870;-0.491480;,
  0.995740;-0.491480;,
  1.243609;-0.491480;,
  1.491479;-0.491480;,
  1.739349;-0.491480;,
  -0.491479;-0.739350;,
  -0.243609;-0.739350;,
  0.004260;-0.739350;,
  0.252130;-0.739350;,
  0.500000;-0.739350;,
  0.747870;-0.739350;,
  0.995740;-0.739350;,
  1.243609;-0.739350;,
  1.491479;-0.739350;,
  1.739349;-0.739350;,
  1.739349;1.739350;,
  1.739349;1.491480;,
  1.739349;1.243610;,
  1.739349;0.995740;,
  1.739349;0.747870;,
  1.739349;0.500000;,
  1.739349;0.252130;,
  1.739349;0.004260;,
  1.739349;-0.243610;,
  1.739349;-0.491480;,
  1.739349;-0.739350;,
  0.000000;0.000000;,
  0.100000;0.000000;,
  0.100000;0.500000;,
  0.000000;0.500000;,
  0.200000;0.000000;,
  0.200000;0.500000;,
  0.300000;0.000000;,
  0.300000;0.500000;,
  0.400000;0.000000;,
  0.400000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.600000;0.000000;,
  0.600000;0.500000;,
  0.700000;0.000000;,
  0.700000;0.500000;,
  0.800000;0.000000;,
  0.800000;0.500000;,
  0.900000;0.000000;,
  0.900000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.100000;1.000000;,
  0.000000;1.000000;,
  0.200000;1.000000;,
  0.300000;1.000000;,
  0.400000;1.000000;,
  0.500000;1.000000;,
  0.600000;1.000000;,
  0.700000;1.000000;,
  0.800000;1.000000;,
  0.900000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.100000;0.500000;,
  0.100000;1.000000;,
  0.000000;1.000000;,
  0.200000;0.500000;,
  0.200000;1.000000;,
  0.300000;0.500000;,
  0.300000;1.000000;,
  0.400000;0.500000;,
  0.400000;1.000000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.600000;0.500000;,
  0.600000;1.000000;,
  0.700000;0.500000;,
  0.700000;1.000000;,
  0.800000;0.500000;,
  0.800000;1.000000;,
  0.900000;0.500000;,
  0.900000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.100000;0.000000;,
  0.200000;0.000000;,
  0.300000;0.000000;,
  0.400000;0.000000;,
  0.500000;0.000000;,
  0.600000;0.000000;,
  0.700000;0.000000;,
  0.800000;0.000000;,
  0.900000;0.000000;,
  1.000000;0.000000;;
 }
}
