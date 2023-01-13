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
 360;
 -2.72728;34.73635;-1.81752;,
 2.82346;34.73635;-1.81752;,
 2.82346;28.98839;-1.81752;,
 -2.72728;28.98839;-1.81752;,
 2.82346;34.73635;-1.81752;,
 2.82346;34.73635;1.83993;,
 2.82346;28.98839;1.83993;,
 2.82346;28.98839;-1.81752;,
 2.82346;34.73635;1.83993;,
 -2.72728;34.73635;1.83993;,
 -2.72728;28.98839;1.83993;,
 2.82346;28.98839;1.83993;,
 -2.72728;34.73635;1.83993;,
 -2.72728;34.73635;-1.81752;,
 -2.72728;28.98839;-1.81752;,
 -2.72728;28.98839;1.83993;,
 2.82346;34.73635;-1.81752;,
 -2.72728;34.73635;-1.81752;,
 -2.72728;28.98839;-1.81752;,
 2.82346;28.98839;-1.81752;,
 -4.74617;29.01917;-1.80734;,
 4.71883;29.01917;-1.80734;,
 4.71883;17.29019;-1.80734;,
 -4.74617;17.29019;-1.80734;,
 4.71883;29.01917;-1.80734;,
 4.71883;29.01917;1.80734;,
 4.71883;17.29019;1.80734;,
 4.71883;17.29019;-1.80734;,
 4.71883;29.01917;1.80734;,
 -4.74617;29.01917;1.80734;,
 -4.74617;17.29019;1.80734;,
 4.71883;17.29019;1.80734;,
 -4.74617;29.01917;1.80734;,
 -4.74617;29.01917;-1.80734;,
 -4.74617;17.29019;-1.80734;,
 -4.74617;17.29019;1.80734;,
 4.71883;29.01917;-1.80734;,
 -4.74617;29.01917;-1.80734;,
 -4.74617;17.29019;-1.80734;,
 4.71883;17.29019;-1.80734;,
 -4.73250;17.35973;-1.80734;,
 4.73250;17.35973;-1.80734;,
 4.73250;12.96891;-1.80734;,
 -4.73250;12.96891;-1.80734;,
 4.73250;17.35973;-1.80734;,
 4.73250;17.35973;1.80734;,
 4.73250;12.96891;1.80734;,
 4.73250;12.96891;-1.80734;,
 4.73250;17.35973;1.80734;,
 -4.73250;17.35973;1.80734;,
 -4.73250;12.96891;1.80734;,
 4.73250;12.96891;1.80734;,
 -4.73250;17.35973;1.80734;,
 -4.73250;17.35973;-1.80734;,
 -4.73250;12.96891;-1.80734;,
 -4.73250;12.96891;1.80734;,
 4.73250;17.35973;-1.80734;,
 -4.73250;17.35973;-1.80734;,
 -4.73250;12.96891;-1.80734;,
 4.73250;12.96891;-1.80734;,
 -4.68942;12.94747;-1.80734;,
 -1.07254;12.94747;-1.80734;,
 -1.07254;7.15296;-1.80734;,
 -4.68942;7.15296;-1.80734;,
 -1.07254;12.94747;-1.80734;,
 -1.07254;12.94747;1.80734;,
 -1.07254;7.15296;1.80734;,
 -1.07254;7.15296;-1.80734;,
 -1.07254;12.94747;1.80734;,
 -4.68942;12.94747;1.80734;,
 -4.68942;7.15296;1.80734;,
 -1.07254;7.15296;1.80734;,
 -4.68942;12.94747;1.80734;,
 -4.68942;12.94747;-1.80734;,
 -4.68942;7.15296;-1.80734;,
 -4.68942;7.15296;1.80734;,
 -1.07254;12.94747;-1.80734;,
 -4.68942;12.94747;-1.80734;,
 -4.68942;7.15296;-1.80734;,
 -1.07254;7.15296;-1.80734;,
 0.95166;12.94747;-1.80734;,
 4.57347;12.94747;-1.80734;,
 4.57347;7.15296;-1.80734;,
 0.95166;7.15296;-1.80734;,
 4.57347;12.94747;-1.80734;,
 4.57347;12.94747;1.80734;,
 4.57347;7.15296;1.80734;,
 4.57347;7.15296;-1.80734;,
 4.57347;12.94747;1.80734;,
 0.95166;12.94747;1.80734;,
 0.95166;7.15296;1.80734;,
 4.57347;7.15296;1.80734;,
 0.95166;12.94747;1.80734;,
 0.95166;12.94747;-1.80734;,
 0.95166;7.15296;-1.80734;,
 0.95166;7.15296;1.80734;,
 4.57347;12.94747;-1.80734;,
 0.95166;12.94747;-1.80734;,
 0.95166;7.15296;-1.80734;,
 4.57347;7.15296;-1.80734;,
 -4.69926;7.12823;-1.80734;,
 -1.07254;7.12823;-1.80734;,
 -1.07254;1.33372;-1.80734;,
 -4.69926;1.33372;-1.80734;,
 -1.07254;7.12823;-1.80734;,
 -1.07254;7.12823;1.80734;,
 -1.07254;1.33372;1.80734;,
 -1.07254;1.33372;-1.80734;,
 -1.07254;7.12823;1.80734;,
 -4.69926;7.12823;1.80734;,
 -4.69926;1.33372;1.80734;,
 -1.07254;1.33372;1.80734;,
 -4.69926;7.12823;1.80734;,
 -4.69926;7.12823;-1.80734;,
 -4.69926;1.33372;-1.80734;,
 -4.69926;1.33372;1.80734;,
 -1.07254;7.12823;-1.80734;,
 -4.69926;7.12823;-1.80734;,
 -4.69926;1.33372;-1.80734;,
 -1.07254;1.33372;-1.80734;,
 0.95166;7.17928;-1.80734;,
 4.46769;7.17928;-1.80734;,
 4.46769;1.38476;-1.80734;,
 0.95166;1.38476;-1.80734;,
 4.46769;7.17928;-1.80734;,
 4.46769;7.17928;1.80734;,
 4.46769;1.38476;1.80734;,
 4.46769;1.38476;-1.80734;,
 4.46769;7.17928;1.80734;,
 0.95166;7.17928;1.80734;,
 0.95166;1.38476;1.80734;,
 4.46769;1.38476;1.80734;,
 0.95166;7.17928;1.80734;,
 0.95166;7.17928;-1.80734;,
 0.95166;1.38476;-1.80734;,
 0.95166;1.38476;1.80734;,
 4.46769;7.17928;-1.80734;,
 0.95166;7.17928;-1.80734;,
 0.95166;1.38476;-1.80734;,
 4.46769;1.38476;-1.80734;,
 -4.66958;1.34588;-1.80734;,
 -1.04494;1.34588;-1.80734;,
 -1.04494;-0.00800;-1.80734;,
 -4.66958;-0.00800;-1.80734;,
 -1.04494;1.34588;-1.80734;,
 -1.04494;1.34588;1.80734;,
 -1.04494;-0.00800;1.80734;,
 -1.04494;-0.00800;-1.80734;,
 -1.04494;1.34588;1.80734;,
 -4.66958;1.34588;1.80734;,
 -4.66958;-0.00800;1.80734;,
 -1.04494;-0.00800;1.80734;,
 -4.66958;1.34588;1.80734;,
 -4.66958;1.34588;-1.80734;,
 -4.66958;-0.00800;-1.80734;,
 -4.66958;-0.00800;1.80734;,
 -1.04494;1.34588;-1.80734;,
 -4.66958;1.34588;-1.80734;,
 -4.66958;-0.00800;-1.80734;,
 -1.04494;-0.00800;-1.80734;,
 0.97212;1.38851;-1.80734;,
 4.38109;1.38851;-1.80734;,
 4.38109;-0.00800;-1.80734;,
 0.97212;-0.00800;-1.80734;,
 4.38109;1.38851;-1.80734;,
 4.38109;1.38851;1.80734;,
 4.38109;-0.00800;1.80734;,
 4.38109;-0.00800;-1.80734;,
 4.38109;1.38851;1.80734;,
 0.97212;1.38851;1.80734;,
 0.97212;-0.00800;1.80734;,
 4.38109;-0.00800;1.80734;,
 0.97212;1.38851;1.80734;,
 0.97212;1.38851;-1.80734;,
 0.97212;-0.00800;-1.80734;,
 0.97212;-0.00800;1.80734;,
 4.38109;1.38851;-1.80734;,
 0.97212;1.38851;-1.80734;,
 0.97212;-0.00800;-1.80734;,
 4.38109;-0.00800;-1.80734;,
 -10.10817;29.02731;-1.80734;,
 -4.69413;29.02731;-1.80734;,
 -4.69413;24.63649;-1.80734;,
 -10.10817;24.63649;-1.80734;,
 -4.69413;29.02731;-1.80734;,
 -4.69413;29.02731;1.80734;,
 -4.69413;24.63649;1.80734;,
 -4.69413;24.63649;-1.80734;,
 -4.69413;29.02731;1.80734;,
 -10.10817;29.02731;1.80734;,
 -10.10817;24.63649;1.80734;,
 -4.69413;24.63649;1.80734;,
 -10.10817;29.02731;1.80734;,
 -10.10817;29.02731;-1.80734;,
 -10.10817;24.63649;-1.80734;,
 -10.10817;24.63649;1.80734;,
 -4.69413;29.02731;-1.80734;,
 -10.10817;29.02731;-1.80734;,
 -10.10817;24.63649;-1.80734;,
 -4.69413;24.63649;-1.80734;,
 -15.36583;29.00183;-1.80734;,
 -9.95179;29.00183;-1.80734;,
 -9.95179;24.61101;-1.80734;,
 -15.36583;24.61101;-1.80734;,
 -9.95179;29.00183;-1.80734;,
 -9.95179;29.00183;1.80734;,
 -9.95179;24.61101;1.80734;,
 -9.95179;24.61101;-1.80734;,
 -9.95179;29.00183;1.80734;,
 -15.36583;29.00183;1.80734;,
 -15.36583;24.61101;1.80734;,
 -9.95179;24.61101;1.80734;,
 -15.36583;29.00183;1.80734;,
 -15.36583;29.00183;-1.80734;,
 -15.36583;24.61101;-1.80734;,
 -15.36583;24.61101;1.80734;,
 -9.95179;29.00183;-1.80734;,
 -15.36583;29.00183;-1.80734;,
 -15.36583;24.61101;-1.80734;,
 -9.95179;24.61101;-1.80734;,
 -18.35056;29.08304;-1.80734;,
 -15.44123;29.08304;-1.80734;,
 -15.44123;24.69222;-1.80734;,
 -18.35056;24.69222;-1.80734;,
 -15.44123;29.08304;-1.80734;,
 -15.44123;29.08304;1.80734;,
 -15.44123;24.69222;1.80734;,
 -15.44123;24.69222;-1.80734;,
 -15.44123;29.08304;1.80734;,
 -18.35056;29.08304;1.80734;,
 -18.35056;24.69222;1.80734;,
 -15.44123;24.69222;1.80734;,
 -18.35056;29.08304;1.80734;,
 -18.35056;29.08304;-1.80734;,
 -18.35056;24.69222;-1.80734;,
 -18.35056;24.69222;1.80734;,
 -15.44123;29.08304;-1.80734;,
 -18.35056;29.08304;-1.80734;,
 -18.35056;24.69222;-1.80734;,
 -15.44123;24.69222;-1.80734;,
 4.58788;28.98771;-1.80734;,
 10.00192;28.98771;-1.80734;,
 10.00192;24.59689;-1.80734;,
 4.58788;24.59689;-1.80734;,
 10.00192;28.98771;-1.80734;,
 10.00192;28.98771;1.80734;,
 10.00192;24.59689;1.80734;,
 10.00192;24.59689;-1.80734;,
 10.00192;28.98771;1.80734;,
 4.58788;28.98771;1.80734;,
 4.58788;24.59689;1.80734;,
 10.00192;24.59689;1.80734;,
 4.58788;28.98771;1.80734;,
 4.58788;28.98771;-1.80734;,
 4.58788;24.59689;-1.80734;,
 4.58788;24.59689;1.80734;,
 10.00192;28.98771;-1.80734;,
 4.58788;28.98771;-1.80734;,
 4.58788;24.59689;-1.80734;,
 10.00192;24.59689;-1.80734;,
 9.84020;28.92874;-1.80734;,
 15.25424;28.92874;-1.80734;,
 15.25424;24.53792;-1.80734;,
 9.84020;24.53792;-1.80734;,
 15.25424;28.92874;-1.80734;,
 15.25424;28.92874;1.80734;,
 15.25424;24.53792;1.80734;,
 15.25424;24.53792;-1.80734;,
 15.25424;28.92874;1.80734;,
 9.84020;28.92874;1.80734;,
 9.84020;24.53792;1.80734;,
 15.25424;24.53792;1.80734;,
 9.84020;28.92874;1.80734;,
 9.84020;28.92874;-1.80734;,
 9.84020;24.53792;-1.80734;,
 9.84020;24.53792;1.80734;,
 15.25424;28.92874;-1.80734;,
 9.84020;28.92874;-1.80734;,
 9.84020;24.53792;-1.80734;,
 15.25424;24.53792;-1.80734;,
 15.21654;28.80406;-1.80734;,
 18.12587;28.80406;-1.80734;,
 18.12587;24.41324;-1.80734;,
 15.21654;24.41324;-1.80734;,
 18.12587;28.80406;-1.80734;,
 18.12587;28.80406;1.80734;,
 18.12587;24.41324;1.80734;,
 18.12587;24.41324;-1.80734;,
 18.12587;28.80406;1.80734;,
 15.21654;28.80406;1.80734;,
 15.21654;24.41324;1.80734;,
 18.12587;24.41324;1.80734;,
 15.21654;28.80406;1.80734;,
 15.21654;28.80406;-1.80734;,
 15.21654;24.41324;-1.80734;,
 15.21654;24.41324;1.80734;,
 18.12587;28.80406;-1.80734;,
 15.21654;28.80406;-1.80734;,
 15.21654;24.41324;-1.80734;,
 18.12587;24.41324;-1.80734;,
 -14.60900;49.10405;-2.58820;,
 14.60900;49.10405;-2.58820;,
 14.60900;46.45342;-2.58820;,
 -14.60900;46.45342;-2.58820;,
 14.60900;49.10405;-2.58820;,
 14.60900;49.10405;2.58820;,
 14.60900;46.45342;2.58820;,
 14.60900;46.45342;-2.58820;,
 14.60900;49.10405;2.58820;,
 -14.60900;49.10405;2.58820;,
 -14.60900;46.45342;2.58820;,
 14.60900;46.45342;2.58820;,
 -14.60900;49.10405;2.58820;,
 -14.60900;49.10405;-2.58820;,
 -14.60900;46.45342;-2.58820;,
 -14.60900;46.45342;2.58820;,
 14.60900;49.10405;-2.58820;,
 -14.60900;49.10405;-2.58820;,
 -14.60900;46.45342;-2.58820;,
 14.60900;46.45342;-2.58820;,
 14.52652;46.98471;-2.79760;,
 17.29420;46.98471;-2.79760;,
 17.29420;0.10803;-2.79760;,
 14.52652;0.10803;-2.79760;,
 17.29420;46.98471;-2.79760;,
 17.29420;46.98471;2.58950;,
 17.29420;0.10803;2.58950;,
 17.29420;0.10803;-2.79760;,
 17.29420;46.98471;2.58950;,
 14.52652;46.98471;2.58950;,
 14.52652;0.10803;2.58950;,
 17.29420;0.10803;2.58950;,
 14.52652;46.98471;2.58950;,
 14.52652;46.98471;-2.79760;,
 14.52652;0.10803;-2.79760;,
 14.52652;0.10803;2.58950;,
 17.29420;46.98471;-2.79760;,
 14.52652;46.98471;-2.79760;,
 14.52652;0.10803;-2.79760;,
 17.29420;0.10803;-2.79760;,
 -17.01546;46.98471;-2.79760;,
 -14.24778;46.98471;-2.79760;,
 -14.24778;0.10803;-2.79760;,
 -17.01546;0.10803;-2.79760;,
 -14.24778;46.98471;-2.79760;,
 -14.24778;46.98471;2.58950;,
 -14.24778;0.10803;2.58950;,
 -14.24778;0.10803;-2.79760;,
 -14.24778;46.98471;2.58950;,
 -17.01546;46.98471;2.58950;,
 -17.01546;0.10803;2.58950;,
 -14.24778;0.10803;2.58950;,
 -17.01546;46.98471;2.58950;,
 -17.01546;46.98471;-2.79760;,
 -17.01546;0.10803;-2.79760;,
 -17.01546;0.10803;2.58950;,
 -14.24778;46.98471;-2.79760;,
 -17.01546;46.98471;-2.79760;,
 -17.01546;0.10803;-2.79760;,
 -14.24778;0.10803;-2.79760;;
 
 108;
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
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;152,145,156,157;,
 4;158,159,146,155;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;172,165,176,177;,
 4;178,179,166,175;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;192,185,196,197;,
 4;198,199,186,195;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;212,205,216,217;,
 4;218,219,206,215;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;232,225,236,237;,
 4;238,239,226,235;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;252,245,256,257;,
 4;258,259,246,255;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;272,265,276,277;,
 4;278,279,266,275;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;288,289,290,291;,
 4;292,293,294,295;,
 4;292,285,296,297;,
 4;298,299,286,295;,
 4;300,301,302,303;,
 4;304,305,306,307;,
 4;308,309,310,311;,
 4;312,313,314,315;,
 4;312,305,316,317;,
 4;318,319,306,315;,
 4;320,321,322,323;,
 4;324,325,326,327;,
 4;328,329,330,331;,
 4;332,333,334,335;,
 4;332,325,336,337;,
 4;338,339,326,335;,
 4;340,341,342,343;,
 4;344,345,346,347;,
 4;348,349,350,351;,
 4;352,353,354,355;,
 4;352,345,356,357;,
 4;358,359,346,355;;
 
 MeshMaterialList {
  1;
  108;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  108;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  108;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;71,71,71,71;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;90,90,90,90;,
  4;91,91,91,91;,
  4;92,92,92,92;,
  4;93,93,93,93;,
  4;94,94,94,94;,
  4;95,95,95,95;,
  4;96,96,96,96;,
  4;97,97,97,97;,
  4;98,98,98,98;,
  4;99,99,99,99;,
  4;100,100,100,100;,
  4;101,101,101,101;,
  4;102,102,102,102;,
  4;103,103,103,103;,
  4;104,104,104,104;,
  4;105,105,105,105;,
  4;106,106,106,106;,
  4;107,107,107,107;;
 }
 MeshTextureCoords {
  360;
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
