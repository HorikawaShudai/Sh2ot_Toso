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
 368;
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
 110.00000;150.00000;-10.00000;,
 110.00000;150.00000;0.00000;,
 110.00000;135.00000;0.00000;,
 110.00000;135.00000;-10.00000;,
 110.00000;150.00000;10.00000;,
 110.00000;135.00000;10.00000;,
 110.00000;120.00000;0.00000;,
 110.00000;120.00000;-10.00000;,
 110.00000;120.00000;10.00000;,
 110.00000;105.00000;0.00000;,
 110.00000;105.00000;-10.00000;,
 110.00000;105.00000;10.00000;,
 110.00000;90.00000;0.00000;,
 110.00000;90.00000;-10.00000;,
 110.00000;90.00000;10.00000;,
 110.00000;75.00000;0.00000;,
 110.00000;75.00000;-10.00000;,
 110.00000;75.00000;10.00000;,
 110.00000;60.00000;0.00000;,
 110.00000;60.00000;-10.00000;,
 110.00000;60.00000;10.00000;,
 110.00000;45.00000;0.00000;,
 110.00000;45.00000;-10.00000;,
 110.00000;45.00000;10.00000;,
 110.00000;30.00000;0.00000;,
 110.00000;30.00000;-10.00000;,
 110.00000;30.00000;10.00000;,
 110.00000;15.00000;0.00000;,
 110.00000;15.00000;-10.00000;,
 110.00000;15.00000;10.00000;,
 110.00000;0.00000;0.00000;,
 110.00000;0.00000;-10.00000;,
 110.00000;0.00000;10.00000;,
 110.00000;150.00000;10.00000;,
 98.00000;150.00000;10.00000;,
 98.00000;135.00000;10.00000;,
 110.00000;135.00000;10.00000;,
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
 110.00000;120.00000;10.00000;,
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
 110.00000;105.00000;10.00000;,
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
 110.00000;90.00000;10.00000;,
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
 110.00000;75.00000;10.00000;,
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
 110.00000;60.00000;10.00000;,
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
 110.00000;45.00000;10.00000;,
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
 110.00000;30.00000;10.00000;,
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
 110.00000;15.00000;10.00000;,
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
 110.00000;0.00000;10.00000;,
 86.00000;0.00000;10.00000;,
 74.00000;0.00000;10.00000;,
 62.00000;0.00000;10.00000;,
 50.00000;0.00000;10.00000;,
 38.00000;0.00000;10.00000;,
 26.00000;0.00000;10.00000;,
 14.00000;0.00000;10.00000;,
 2.00000;0.00000;10.00000;,
 -10.00000;0.00000;10.00000;,
 -10.00000;150.00000;10.00000;,
 -10.00000;150.00000;0.00000;,
 -10.00000;135.00000;0.00000;,
 -10.00000;135.00000;10.00000;,
 -10.00000;150.00000;-10.00000;,
 -10.00000;135.00000;-10.00000;,
 -10.00000;120.00000;0.00000;,
 -10.00000;120.00000;10.00000;,
 -10.00000;120.00000;-10.00000;,
 -10.00000;105.00000;0.00000;,
 -10.00000;105.00000;10.00000;,
 -10.00000;105.00000;-10.00000;,
 -10.00000;90.00000;0.00000;,
 -10.00000;90.00000;10.00000;,
 -10.00000;90.00000;-10.00000;,
 -10.00000;75.00000;0.00000;,
 -10.00000;75.00000;10.00000;,
 -10.00000;75.00000;-10.00000;,
 -10.00000;60.00000;0.00000;,
 -10.00000;60.00000;10.00000;,
 -10.00000;60.00000;-10.00000;,
 -10.00000;45.00000;0.00000;,
 -10.00000;45.00000;10.00000;,
 -10.00000;45.00000;-10.00000;,
 -10.00000;30.00000;0.00000;,
 -10.00000;30.00000;10.00000;,
 -10.00000;30.00000;-10.00000;,
 -10.00000;15.00000;0.00000;,
 -10.00000;15.00000;10.00000;,
 -10.00000;15.00000;-10.00000;,
 -10.00000;0.00000;0.00000;,
 -10.00000;0.00000;10.00000;,
 -10.00000;0.00000;-10.00000;,
 2.00000;150.00000;10.00000;,
 2.00000;150.00000;0.00000;,
 -10.00000;150.00000;0.00000;,
 14.00000;150.00000;10.00000;,
 14.00000;150.00000;0.00000;,
 26.00000;150.00000;10.00000;,
 26.00000;150.00000;0.00000;,
 38.00000;150.00000;10.00000;,
 38.00000;150.00000;0.00000;,
 50.00000;150.00000;0.00000;,
 62.00000;150.00000;10.00000;,
 62.00000;150.00000;0.00000;,
 74.00000;150.00000;10.00000;,
 74.00000;150.00000;0.00000;,
 86.00000;150.00000;10.00000;,
 86.00000;150.00000;0.00000;,
 98.00000;150.00000;10.00000;,
 98.00000;150.00000;0.00000;,
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
 14.00000;0.00000;0.00000;,
 14.00000;0.00000;10.00000;,
 26.00000;0.00000;0.00000;,
 26.00000;0.00000;10.00000;,
 38.00000;0.00000;0.00000;,
 38.00000;0.00000;10.00000;,
 50.00000;0.00000;0.00000;,
 62.00000;0.00000;0.00000;,
 62.00000;0.00000;10.00000;,
 74.00000;0.00000;0.00000;,
 74.00000;0.00000;10.00000;,
 86.00000;0.00000;0.00000;,
 86.00000;0.00000;10.00000;,
 98.00000;0.00000;0.00000;,
 98.00000;0.00000;10.00000;,
 110.00000;0.00000;0.00000;,
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
 4;121,122,123,124;,
 4;122,125,126,123;,
 4;124,123,127,128;,
 4;123,126,129,127;,
 4;128,127,130,131;,
 4;127,129,132,130;,
 4;131,130,133,134;,
 4;130,132,135,133;,
 4;134,133,136,137;,
 4;133,135,138,136;,
 4;137,136,139,140;,
 4;136,138,141,139;,
 4;140,139,142,143;,
 4;139,141,144,142;,
 4;143,142,145,146;,
 4;142,144,147,145;,
 4;146,145,148,149;,
 4;145,147,150,148;,
 4;149,148,151,152;,
 4;148,150,153,151;,
 4;154,155,156,157;,
 4;155,158,159,156;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;162,164,165,163;,
 4;164,166,167,165;,
 4;166,168,169,167;,
 4;168,170,171,169;,
 4;170,172,173,171;,
 4;172,174,175,173;,
 4;157,156,176,177;,
 4;156,159,178,176;,
 4;159,161,179,178;,
 4;161,163,180,179;,
 4;163,165,181,180;,
 4;165,167,182,181;,
 4;167,169,183,182;,
 4;169,171,184,183;,
 4;171,173,185,184;,
 4;173,175,186,185;,
 4;177,176,187,188;,
 4;176,178,189,187;,
 4;178,179,190,189;,
 4;179,180,191,190;,
 4;180,181,192,191;,
 4;181,182,193,192;,
 4;182,183,194,193;,
 4;183,184,195,194;,
 4;184,185,196,195;,
 4;185,186,197,196;,
 4;188,187,198,199;,
 4;187,189,200,198;,
 4;189,190,201,200;,
 4;190,191,202,201;,
 4;191,192,203,202;,
 4;192,193,204,203;,
 4;193,194,205,204;,
 4;194,195,206,205;,
 4;195,196,207,206;,
 4;196,197,208,207;,
 4;199,198,209,210;,
 4;198,200,211,209;,
 4;200,201,212,211;,
 4;201,202,213,212;,
 4;202,203,214,213;,
 4;203,204,215,214;,
 4;204,205,216,215;,
 4;205,206,217,216;,
 4;206,207,218,217;,
 4;207,208,219,218;,
 4;210,209,220,221;,
 4;209,211,222,220;,
 4;211,212,223,222;,
 4;212,213,224,223;,
 4;213,214,225,224;,
 4;214,215,226,225;,
 4;215,216,227,226;,
 4;216,217,228,227;,
 4;217,218,229,228;,
 4;218,219,230,229;,
 4;221,220,231,232;,
 4;220,222,233,231;,
 4;222,223,234,233;,
 4;223,224,235,234;,
 4;224,225,236,235;,
 4;225,226,237,236;,
 4;226,227,238,237;,
 4;227,228,239,238;,
 4;228,229,240,239;,
 4;229,230,241,240;,
 4;232,231,242,243;,
 4;231,233,244,242;,
 4;233,234,245,244;,
 4;234,235,246,245;,
 4;235,236,247,246;,
 4;236,237,248,247;,
 4;237,238,249,248;,
 4;238,239,250,249;,
 4;239,240,251,250;,
 4;240,241,252,251;,
 4;243,242,253,254;,
 4;242,244,255,253;,
 4;244,245,256,255;,
 4;245,246,257,256;,
 4;246,247,258,257;,
 4;247,248,259,258;,
 4;248,249,260,259;,
 4;249,250,261,260;,
 4;250,251,262,261;,
 4;251,252,263,262;,
 4;254,253,264,265;,
 4;253,255,266,264;,
 4;255,256,267,266;,
 4;256,257,268,267;,
 4;257,258,269,268;,
 4;258,259,270,269;,
 4;259,260,271,270;,
 4;260,261,272,271;,
 4;261,262,273,272;,
 4;262,263,274,273;,
 4;275,276,277,278;,
 4;276,279,280,277;,
 4;278,277,281,282;,
 4;277,280,283,281;,
 4;282,281,284,285;,
 4;281,283,286,284;,
 4;285,284,287,288;,
 4;284,286,289,287;,
 4;288,287,290,291;,
 4;287,289,292,290;,
 4;291,290,293,294;,
 4;290,292,295,293;,
 4;294,293,296,297;,
 4;293,295,298,296;,
 4;297,296,299,300;,
 4;296,298,301,299;,
 4;300,299,302,303;,
 4;299,301,304,302;,
 4;303,302,305,306;,
 4;302,304,307,305;,
 4;275,308,309,310;,
 4;308,311,312,309;,
 4;311,313,314,312;,
 4;313,315,316,314;,
 4;315,164,317,316;,
 4;164,318,319,317;,
 4;318,320,321,319;,
 4;320,322,323,321;,
 4;322,324,325,323;,
 4;324,125,326,325;,
 4;310,309,327,328;,
 4;309,312,329,327;,
 4;312,314,330,329;,
 4;314,316,331,330;,
 4;316,317,332,331;,
 4;317,319,333,332;,
 4;319,321,334,333;,
 4;321,323,335,334;,
 4;323,325,336,335;,
 4;325,326,337,336;,
 4;338,339,340,306;,
 4;339,341,342,340;,
 4;341,343,344,342;,
 4;343,345,346,344;,
 4;345,347,269,346;,
 4;347,348,349,269;,
 4;348,350,351,349;,
 4;350,352,353,351;,
 4;352,354,355,353;,
 4;354,356,153,355;,
 4;357,358,339,338;,
 4;358,359,341,339;,
 4;359,360,343,341;,
 4;360,361,345,343;,
 4;361,362,347,345;,
 4;362,363,348,347;,
 4;363,364,350,348;,
 4;364,365,352,350;,
 4;365,366,354,352;,
 4;366,367,356,354;;
 
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
    "Data\\TEXTURE\\Concretewall2.jpg";
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
  368;
  0.000000;0.000000;,
  0.100000;0.000000;,
  0.100000;0.100000;,
  0.000000;0.100000;,
  0.200000;0.000000;,
  0.200000;0.100000;,
  0.300000;0.000000;,
  0.300000;0.100000;,
  0.400000;0.000000;,
  0.400000;0.100000;,
  0.500000;0.000000;,
  0.500000;0.100000;,
  0.600000;0.000000;,
  0.600000;0.100000;,
  0.700000;0.000000;,
  0.700000;0.100000;,
  0.800000;0.000000;,
  0.800000;0.100000;,
  0.900000;0.000000;,
  0.900000;0.100000;,
  1.000000;0.000000;,
  1.000000;0.100000;,
  0.100000;0.200000;,
  0.000000;0.200000;,
  0.200000;0.200000;,
  0.300000;0.200000;,
  0.400000;0.200000;,
  0.500000;0.200000;,
  0.600000;0.200000;,
  0.700000;0.200000;,
  0.800000;0.200000;,
  0.900000;0.200000;,
  1.000000;0.200000;,
  0.100000;0.300000;,
  0.000000;0.300000;,
  0.200000;0.300000;,
  0.300000;0.300000;,
  0.400000;0.300000;,
  0.500000;0.300000;,
  0.600000;0.300000;,
  0.700000;0.300000;,
  0.800000;0.300000;,
  0.900000;0.300000;,
  1.000000;0.300000;,
  0.100000;0.400000;,
  0.000000;0.400000;,
  0.200000;0.400000;,
  0.300000;0.400000;,
  0.400000;0.400000;,
  0.500000;0.400000;,
  0.600000;0.400000;,
  0.700000;0.400000;,
  0.800000;0.400000;,
  0.900000;0.400000;,
  1.000000;0.400000;,
  0.100000;0.500000;,
  0.000000;0.500000;,
  0.200000;0.500000;,
  0.300000;0.500000;,
  0.400000;0.500000;,
  0.500000;0.500000;,
  0.600000;0.500000;,
  0.700000;0.500000;,
  0.800000;0.500000;,
  0.900000;0.500000;,
  1.000000;0.500000;,
  0.100000;0.600000;,
  0.000000;0.600000;,
  0.200000;0.600000;,
  0.300000;0.600000;,
  0.400000;0.600000;,
  0.500000;0.600000;,
  0.600000;0.600000;,
  0.700000;0.600000;,
  0.800000;0.600000;,
  0.900000;0.600000;,
  1.000000;0.600000;,
  0.100000;0.700000;,
  0.000000;0.700000;,
  0.200000;0.700000;,
  0.300000;0.700000;,
  0.400000;0.700000;,
  0.500000;0.700000;,
  0.600000;0.700000;,
  0.700000;0.700000;,
  0.800000;0.700000;,
  0.900000;0.700000;,
  1.000000;0.700000;,
  0.100000;0.800000;,
  0.000000;0.800000;,
  0.200000;0.800000;,
  0.300000;0.800000;,
  0.400000;0.800000;,
  0.500000;0.800000;,
  0.600000;0.800000;,
  0.700000;0.800000;,
  0.800000;0.800000;,
  0.900000;0.800000;,
  1.000000;0.800000;,
  0.100000;0.900000;,
  0.000000;0.900000;,
  0.200000;0.900000;,
  0.300000;0.900000;,
  0.400000;0.900000;,
  0.500000;0.900000;,
  0.600000;0.900000;,
  0.700000;0.900000;,
  0.800000;0.900000;,
  0.900000;0.900000;,
  1.000000;0.900000;,
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
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.100000;,
  0.000000;0.100000;,
  1.000000;0.000000;,
  1.000000;0.100000;,
  0.500000;0.200000;,
  0.000000;0.200000;,
  1.000000;0.200000;,
  0.500000;0.300000;,
  0.000000;0.300000;,
  1.000000;0.300000;,
  0.500000;0.400000;,
  0.000000;0.400000;,
  1.000000;0.400000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.600000;,
  0.000000;0.600000;,
  1.000000;0.600000;,
  0.500000;0.700000;,
  0.000000;0.700000;,
  1.000000;0.700000;,
  0.500000;0.800000;,
  0.000000;0.800000;,
  1.000000;0.800000;,
  0.500000;0.900000;,
  0.000000;0.900000;,
  1.000000;0.900000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.100000;0.000000;,
  0.100000;0.100000;,
  0.000000;0.100000;,
  0.200000;0.000000;,
  0.200000;0.100000;,
  0.300000;0.000000;,
  0.300000;0.100000;,
  0.400000;0.000000;,
  0.400000;0.100000;,
  0.500000;0.000000;,
  0.500000;0.100000;,
  0.600000;0.000000;,
  0.600000;0.100000;,
  0.700000;0.000000;,
  0.700000;0.100000;,
  0.800000;0.000000;,
  0.800000;0.100000;,
  0.900000;0.000000;,
  0.900000;0.100000;,
  1.000000;0.000000;,
  1.000000;0.100000;,
  0.100000;0.200000;,
  0.000000;0.200000;,
  0.200000;0.200000;,
  0.300000;0.200000;,
  0.400000;0.200000;,
  0.500000;0.200000;,
  0.600000;0.200000;,
  0.700000;0.200000;,
  0.800000;0.200000;,
  0.900000;0.200000;,
  1.000000;0.200000;,
  0.100000;0.300000;,
  0.000000;0.300000;,
  0.200000;0.300000;,
  0.300000;0.300000;,
  0.400000;0.300000;,
  0.500000;0.300000;,
  0.600000;0.300000;,
  0.700000;0.300000;,
  0.800000;0.300000;,
  0.900000;0.300000;,
  1.000000;0.300000;,
  0.100000;0.400000;,
  0.000000;0.400000;,
  0.200000;0.400000;,
  0.300000;0.400000;,
  0.400000;0.400000;,
  0.500000;0.400000;,
  0.600000;0.400000;,
  0.700000;0.400000;,
  0.800000;0.400000;,
  0.900000;0.400000;,
  1.000000;0.400000;,
  0.100000;0.500000;,
  0.000000;0.500000;,
  0.200000;0.500000;,
  0.300000;0.500000;,
  0.400000;0.500000;,
  0.500000;0.500000;,
  0.600000;0.500000;,
  0.700000;0.500000;,
  0.800000;0.500000;,
  0.900000;0.500000;,
  1.000000;0.500000;,
  0.100000;0.600000;,
  0.000000;0.600000;,
  0.200000;0.600000;,
  0.300000;0.600000;,
  0.400000;0.600000;,
  0.500000;0.600000;,
  0.600000;0.600000;,
  0.700000;0.600000;,
  0.800000;0.600000;,
  0.900000;0.600000;,
  1.000000;0.600000;,
  0.100000;0.700000;,
  0.000000;0.700000;,
  0.200000;0.700000;,
  0.300000;0.700000;,
  0.400000;0.700000;,
  0.500000;0.700000;,
  0.600000;0.700000;,
  0.700000;0.700000;,
  0.800000;0.700000;,
  0.900000;0.700000;,
  1.000000;0.700000;,
  0.100000;0.800000;,
  0.000000;0.800000;,
  0.200000;0.800000;,
  0.300000;0.800000;,
  0.400000;0.800000;,
  0.500000;0.800000;,
  0.600000;0.800000;,
  0.700000;0.800000;,
  0.800000;0.800000;,
  0.900000;0.800000;,
  1.000000;0.800000;,
  0.100000;0.900000;,
  0.000000;0.900000;,
  0.200000;0.900000;,
  0.300000;0.900000;,
  0.400000;0.900000;,
  0.500000;0.900000;,
  0.600000;0.900000;,
  0.700000;0.900000;,
  0.800000;0.900000;,
  0.900000;0.900000;,
  1.000000;0.900000;,
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
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.100000;,
  0.000000;0.100000;,
  1.000000;0.000000;,
  1.000000;0.100000;,
  0.500000;0.200000;,
  0.000000;0.200000;,
  1.000000;0.200000;,
  0.500000;0.300000;,
  0.000000;0.300000;,
  1.000000;0.300000;,
  0.500000;0.400000;,
  0.000000;0.400000;,
  1.000000;0.400000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.600000;,
  0.000000;0.600000;,
  1.000000;0.600000;,
  0.500000;0.700000;,
  0.000000;0.700000;,
  1.000000;0.700000;,
  0.500000;0.800000;,
  0.000000;0.800000;,
  1.000000;0.800000;,
  0.500000;0.900000;,
  0.000000;0.900000;,
  1.000000;0.900000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.100000;0.000000;,
  0.100000;0.500000;,
  0.000000;0.500000;,
  0.200000;0.000000;,
  0.200000;0.500000;,
  0.300000;0.000000;,
  0.300000;0.500000;,
  0.400000;0.000000;,
  0.400000;0.500000;,
  0.500000;0.500000;,
  0.600000;0.000000;,
  0.600000;0.500000;,
  0.700000;0.000000;,
  0.700000;0.500000;,
  0.800000;0.000000;,
  0.800000;0.500000;,
  0.900000;0.000000;,
  0.900000;0.500000;,
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
  0.200000;0.500000;,
  0.200000;1.000000;,
  0.300000;0.500000;,
  0.300000;1.000000;,
  0.400000;0.500000;,
  0.400000;1.000000;,
  0.500000;0.500000;,
  0.600000;0.500000;,
  0.600000;1.000000;,
  0.700000;0.500000;,
  0.700000;1.000000;,
  0.800000;0.500000;,
  0.800000;1.000000;,
  0.900000;0.500000;,
  0.900000;1.000000;,
  1.000000;0.500000;,
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
