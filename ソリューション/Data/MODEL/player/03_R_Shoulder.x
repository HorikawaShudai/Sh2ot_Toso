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
 240;
 -0.80375;-0.54605;1.51723;,
 -0.80375;0.12986;1.82720;,
 -1.14297;-0.50516;1.43099;,
 -0.85010;0.71407;1.45184;,
 -1.68747;-0.50582;1.32602;,
 -0.13785;1.01555;1.47670;,
 -1.66093;0.51065;1.61161;,
 -0.85620;1.03288;1.35000;,
 -1.36927;1.51455;1.08793;,
 -0.80375;1.14872;1.22645;,
 -1.14297;1.48625;0.87797;,
 -0.80375;1.29731;0.46757;,
 -1.36308;1.61614;0.64417;,
 -1.14297;1.54257;0.34454;,
 -1.35692;1.61088;0.14496;,
 -0.80375;1.07261;-1.15839;,
 -1.14297;1.39108;-1.02755;,
 -0.80375;1.22514;-0.49249;,
 -1.14297;1.51230;-0.27538;,
 -1.37306;1.46880;-0.95134;,
 -1.35662;1.59958;-0.42748;,
 -0.55486;-0.15094;-1.54716;,
 -1.07430;-0.47667;-1.49239;,
 -0.87680;0.22292;-1.62041;,
 -1.14297;0.45477;-1.77193;,
 -1.48583;-0.50543;-1.64617;,
 -1.44395;0.61844;-1.67737;,
 -0.67607;-0.60502;-1.53573;,
 -1.12591;-0.65748;-1.27105;,
 -0.84129;-0.91451;-0.36662;,
 -1.44544;-0.83144;-1.12602;,
 -1.14297;-0.98240;-0.48566;,
 -1.37564;-0.88138;-0.45023;,
 -0.99814;-0.82464;0.85125;,
 -1.32972;-0.94553;0.61503;,
 -1.69806;-0.79756;0.49873;,
 -1.90427;1.43313;1.04946;,
 -2.16754;0.29424;1.38426;,
 -2.47944;1.23202;0.94150;,
 -2.07348;-0.47059;1.21630;,
 -2.71473;0.24327;1.35771;,
 -2.47727;-0.49108;1.16493;,
 -1.91370;1.54407;0.59902;,
 -2.48083;1.34260;0.58398;,
 -1.87132;1.55000;0.15816;,
 -2.42953;1.35867;0.16780;,
 -1.89133;1.54127;-0.44027;,
 -2.44223;1.42666;-0.50745;,
 -1.87388;1.46139;-1.05461;,
 -2.43491;1.35670;-1.12223;,
 -1.87371;-0.52329;-1.54195;,
 -1.87054;0.74478;-1.74129;,
 -2.26726;-0.36310;-1.62856;,
 -2.46736;0.67568;-1.78642;,
 -1.88193;-0.80704;-0.44768;,
 -1.92045;-0.76544;-1.10401;,
 -2.48692;-0.61218;-0.46260;,
 -2.46840;-0.70723;-1.33480;,
 -1.92810;-0.71130;0.40948;,
 -2.54745;-0.69918;0.38203;,
 -3.43293;0.42988;-0.60917;,
 -3.43293;0.28607;-0.55508;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.18080;-0.40732;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.14227;-0.20544;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.18080;-0.00357;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.28607;0.14420;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.42988;0.19829;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.57369;0.14420;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.67895;-0.00357;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.71748;-0.20544;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.67895;-0.40732;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.57369;-0.55508;,
 -3.48177;0.42988;-0.20544;,
 -3.43293;0.42988;-0.60917;,
 -3.48177;0.42988;-0.20544;,
 -0.93102;-1.07692;0.96218;,
 -0.80375;-0.54605;1.51723;,
 -0.99814;-0.82464;0.85125;,
 -0.84129;-0.91451;-0.36662;,
 -0.33528;-0.73348;1.74361;,
 -0.80375;-0.54605;1.51723;,
 -0.60898;-0.82409;-1.02900;,
 -0.84129;-0.91451;-0.36662;,
 -0.67607;-0.60502;-1.53573;,
 -0.31973;-0.73348;-1.41958;,
 -0.01536;0.01919;1.70393;,
 -0.13785;1.01555;1.47670;,
 -0.80375;0.12986;1.82720;,
 -0.55486;-0.15094;-1.54716;,
 -0.43596;0.02961;-1.29247;,
 -0.47816;1.20509;1.01203;,
 -0.80375;1.14872;1.22645;,
 -0.43596;0.02961;-1.29247;,
 -0.55486;-0.15094;-1.54716;,
 -0.87680;0.22292;-1.62041;,
 -0.49681;1.33368;0.42652;,
 -0.80375;1.29731;0.46757;,
 -0.43596;0.02961;-1.29247;,
 -0.80375;1.07261;-1.15839;,
 -0.09630;0.96503;-0.82799;,
 -0.45655;1.20511;-0.31421;,
 -0.80375;1.22514;-0.49249;,
 -2.26726;-0.36310;-1.62856;,
 -2.79216;-0.01271;-1.28151;,
 -2.79216;0.42988;-1.44798;,
 -2.46736;0.67568;-1.78642;,
 -2.46840;-0.70723;-1.33480;,
 -2.79216;-0.33671;-0.82672;,
 -2.48692;-0.61218;-0.46260;,
 -2.79216;-0.45527;-0.20544;,
 -2.54745;-0.69918;0.38203;,
 -2.79216;-0.33671;0.41584;,
 -2.47727;-0.49108;1.16493;,
 -2.79216;-0.01271;0.87064;,
 -2.71473;0.24327;1.35771;,
 -2.79216;0.42988;1.03710;,
 -2.47944;1.23202;0.94150;,
 -2.79216;0.87245;0.87064;,
 -2.48083;1.34260;0.58398;,
 -2.79216;1.19645;0.41584;,
 -2.42953;1.35867;0.16780;,
 -2.79216;1.31502;-0.20544;,
 -2.44223;1.42666;-0.50745;,
 -2.79216;1.19645;-0.82672;,
 -2.43491;1.35670;-1.12223;,
 -2.79216;0.87245;-1.28151;,
 -2.46736;0.67568;-1.78642;,
 -2.79216;0.42988;-1.44798;,
 -3.07037;0.05340;-1.12080;,
 -3.07037;0.42988;-1.26241;,
 -3.07037;-0.22220;-0.73392;,
 -3.07037;-0.32309;-0.20544;,
 -3.07037;-0.22220;0.32305;,
 -3.07037;0.05340;0.70993;,
 -3.07037;0.42988;0.85152;,
 -3.07037;0.80636;0.70993;,
 -3.07037;1.08195;0.32305;,
 -3.07037;1.18284;-0.20544;,
 -3.07037;1.08196;-0.73392;,
 -3.07037;0.80636;-1.12080;,
 -3.07037;0.42988;-1.26241;,
 -3.29117;0.15634;-0.87050;,
 -3.29117;0.42988;-0.97338;,
 -3.29117;-0.04388;-0.58941;,
 -3.29117;-0.11718;-0.20544;,
 -3.29117;0.15634;0.45961;,
 -3.29117;-0.04388;0.17853;,
 -3.29117;0.42988;0.56249;,
 -3.29117;0.70340;0.45961;,
 -3.29117;0.90363;0.17853;,
 -3.29117;0.97693;-0.20544;,
 -3.29117;0.90363;-0.58941;,
 -3.29117;0.70340;-0.87050;,
 -3.29117;0.42988;-0.97338;,
 0.95829;0.06686;0.11084;,
 0.90266;-0.12304;-0.18466;,
 0.90266;0.06686;-0.24042;,
 0.95829;0.06686;0.11084;,
 0.90266;-0.25265;-0.03508;,
 0.95829;0.06686;0.11084;,
 0.90266;-0.28083;0.16083;,
 0.95829;0.06686;0.11084;,
 0.90266;-0.19862;0.34087;,
 0.95829;0.06686;0.11084;,
 0.90266;-0.03209;0.44787;,
 0.95829;0.06686;0.11084;,
 0.90266;0.16584;0.44787;,
 0.95829;0.06686;0.11084;,
 0.90266;0.33234;0.34087;,
 0.95829;0.06686;0.11084;,
 0.90266;0.41456;0.16083;,
 0.95829;0.06686;0.11084;,
 0.90266;0.38638;-0.03508;,
 0.95829;0.06686;0.11084;,
 0.90266;0.25679;-0.18466;,
 0.95829;0.06686;0.11084;,
 0.90266;0.06686;-0.24042;,
 0.74120;-0.29437;-0.45124;,
 0.74120;0.06686;-0.55730;,
 0.74120;-0.54091;-0.16672;,
 0.74120;-0.59450;0.20593;,
 0.74120;-0.43808;0.54838;,
 0.74120;-0.12138;0.75192;,
 0.74120;0.25510;0.75192;,
 0.74120;0.57182;0.54838;,
 0.74120;0.72823;0.20593;,
 0.74120;0.67464;-0.16672;,
 0.74120;0.42810;-0.45124;,
 0.74120;0.06686;-0.55730;,
 0.48973;-0.43033;-0.66279;,
 0.48973;0.06686;-0.80878;,
 0.48973;-0.76965;-0.27118;,
 0.48973;-0.84341;0.24172;,
 0.48973;-0.62814;0.71306;,
 0.48973;-0.19222;0.99321;,
 0.48973;0.32595;0.99321;,
 0.48973;0.76188;0.71306;,
 0.48973;0.97713;0.24172;,
 0.48973;0.90339;-0.27118;,
 0.48973;0.56406;-0.66279;,
 0.48973;0.06686;-0.80878;,
 0.17284;-0.51760;-0.79862;,
 0.17284;0.06686;-0.97024;,
 0.17284;-0.91652;-0.33826;,
 0.17284;-1.00322;0.26469;,
 0.17284;-0.75015;0.81879;,
 0.17284;-0.23771;1.14812;,
 0.17284;0.37145;1.14812;,
 0.17284;0.88390;0.81879;,
 0.17284;1.13694;0.26469;,
 0.17284;1.05023;-0.33826;,
 0.17284;0.65133;-0.79862;,
 0.17284;0.06686;-0.97024;,
 -0.31973;-0.73348;-1.41958;,
 -0.43596;0.02961;-1.29247;,
 -0.60898;-0.82409;-1.02900;,
 -0.84129;-0.91451;-0.36662;,
 -0.93102;-1.07692;0.96218;,
 -0.33528;-0.73348;1.74361;,
 -0.01536;0.01919;1.70393;,
 -0.49681;1.33368;0.42652;,
 -0.47816;1.20509;1.01203;,
 -0.45655;1.20511;-0.31421;,
 -0.09630;0.96503;-0.82799;,
 -0.43596;0.02961;-1.29247;,
 -3.20872;-0.15639;-0.00810;,
 -3.22133;-0.10028;0.22424;,
 -3.19801;-0.20405;-0.20544;,
 0.17284;0.60002;1.00123;,
 -0.13785;1.01555;1.47670;;
 
 283;
 3;0,1,2;,
 3;1,3,2;,
 3;2,3,4;,
 3;1,5,3;,
 3;4,3,6;,
 3;3,7,6;,
 3;6,7,8;,
 3;3,5,7;,
 3;5,9,7;,
 3;9,10,7;,
 3;7,10,8;,
 3;9,11,10;,
 3;8,10,12;,
 3;10,13,12;,
 3;12,13,14;,
 3;10,11,13;,
 3;15,16,17;,
 3;16,18,17;,
 3;17,18,11;,
 3;16,19,18;,
 3;11,18,13;,
 3;18,20,13;,
 3;13,20,14;,
 3;18,19,20;,
 3;21,22,23;,
 3;22,24,23;,
 3;23,24,15;,
 3;22,25,24;,
 3;15,24,16;,
 3;24,26,16;,
 3;16,26,19;,
 3;24,25,26;,
 3;21,27,22;,
 3;27,28,22;,
 3;22,28,25;,
 3;27,29,28;,
 3;25,28,30;,
 3;28,31,30;,
 3;30,31,32;,
 3;28,29,31;,
 3;0,2,33;,
 3;2,34,33;,
 3;33,34,29;,
 3;2,4,34;,
 3;29,34,31;,
 3;34,35,31;,
 3;31,35,32;,
 3;34,4,35;,
 3;8,36,6;,
 3;36,37,6;,
 3;6,37,4;,
 3;36,38,37;,
 3;4,37,39;,
 3;37,40,39;,
 3;39,40,41;,
 3;37,38,40;,
 3;8,12,36;,
 3;12,42,36;,
 3;36,42,38;,
 3;12,14,42;,
 3;38,42,43;,
 3;42,44,43;,
 3;43,44,45;,
 3;42,14,44;,
 3;14,20,44;,
 3;20,46,44;,
 3;44,46,45;,
 3;20,19,46;,
 3;45,46,47;,
 3;46,48,47;,
 3;47,48,49;,
 3;46,19,48;,
 3;25,50,26;,
 3;50,51,26;,
 3;26,51,19;,
 3;50,52,51;,
 3;19,51,48;,
 3;51,53,48;,
 3;48,53,49;,
 3;51,52,53;,
 3;32,54,30;,
 3;54,55,30;,
 3;30,55,25;,
 3;54,56,55;,
 3;25,55,50;,
 3;55,57,50;,
 3;50,57,52;,
 3;55,56,57;,
 3;4,39,35;,
 3;39,58,35;,
 3;35,58,32;,
 3;39,41,58;,
 3;32,58,54;,
 3;58,59,54;,
 3;54,59,56;,
 3;58,41,59;,
 3;60,61,62;,
 3;61,63,64;,
 3;63,65,66;,
 3;65,67,68;,
 3;67,69,70;,
 3;69,71,72;,
 3;71,73,74;,
 3;73,75,76;,
 3;75,77,78;,
 3;77,79,80;,
 3;79,81,82;,
 3;81,83,84;,
 3;85,86,87;,
 3;85,87,88;,
 3;85,89,90;,
 3;91,92,93;,
 3;91,93,94;,
 3;89,95,90;,
 3;95,96,97;,
 3;95,97,90;,
 3;94,93,98;,
 3;94,98,99;,
 3;100,101,96;,
 3;100,96,95;,
 3;102,103,104;,
 3;105,106,101;,
 3;105,101,100;,
 3;107,104,108;,
 3;107,108,109;,
 3;110,111,106;,
 3;110,106,105;,
 3;109,108,111;,
 3;109,111,110;,
 3;112,113,114;,
 3;112,114,115;,
 3;116,117,113;,
 3;116,113,112;,
 3;118,119,117;,
 3;118,117,116;,
 3;120,121,119;,
 3;120,119,118;,
 3;122,123,121;,
 3;122,121,120;,
 3;124,125,123;,
 3;124,123,122;,
 3;126,127,125;,
 3;126,125,124;,
 3;126,128,129;,
 3;126,129,127;,
 3;130,131,129;,
 3;130,129,128;,
 3;132,133,131;,
 3;132,131,130;,
 3;134,135,133;,
 3;134,133,132;,
 3;136,137,135;,
 3;136,135,134;,
 3;113,138,139;,
 3;113,139,114;,
 3;117,140,138;,
 3;117,138,113;,
 3;119,141,140;,
 3;119,140,117;,
 3;121,142,141;,
 3;121,141,119;,
 3;123,143,142;,
 3;123,142,121;,
 3;125,144,143;,
 3;125,143,123;,
 3;127,145,144;,
 3;127,144,125;,
 3;129,146,145;,
 3;129,145,127;,
 3;131,147,146;,
 3;131,146,129;,
 3;133,148,147;,
 3;133,147,131;,
 3;135,149,148;,
 3;135,148,133;,
 3;137,150,149;,
 3;137,149,135;,
 3;138,151,152;,
 3;138,152,139;,
 3;140,153,151;,
 3;140,151,138;,
 3;141,154,153;,
 3;141,153,140;,
 3;143,155,156;,
 3;143,156,142;,
 3;144,157,155;,
 3;144,155,143;,
 3;145,158,157;,
 3;145,157,144;,
 3;146,159,158;,
 3;146,158,145;,
 3;147,160,159;,
 3;147,159,146;,
 3;148,161,160;,
 3;148,160,147;,
 3;149,162,161;,
 3;149,161,148;,
 3;150,163,162;,
 3;150,162,149;,
 3;151,61,60;,
 3;151,60,152;,
 3;151,153,63;,
 3;151,63,61;,
 3;154,65,63;,
 3;154,63,153;,
 3;156,67,65;,
 3;156,65,154;,
 3;155,69,67;,
 3;155,67,156;,
 3;157,71,69;,
 3;157,69,155;,
 3;158,73,71;,
 3;158,71,157;,
 3;159,75,73;,
 3;159,73,158;,
 3;160,77,75;,
 3;160,75,159;,
 3;161,79,77;,
 3;161,77,160;,
 3;162,81,79;,
 3;162,79,161;,
 3;163,83,81;,
 3;163,81,162;,
 3;164,165,166;,
 3;167,168,165;,
 3;169,170,168;,
 3;171,172,170;,
 3;173,174,172;,
 3;175,176,174;,
 3;177,178,176;,
 3;179,180,178;,
 3;181,182,180;,
 3;183,184,182;,
 3;185,186,184;,
 4;166,165,187,188;,
 4;165,168,189,187;,
 4;168,170,190,189;,
 4;170,172,191,190;,
 4;172,174,192,191;,
 4;174,176,193,192;,
 4;176,178,194,193;,
 4;178,180,195,194;,
 4;180,182,196,195;,
 4;182,184,197,196;,
 4;184,186,198,197;,
 4;188,187,199,200;,
 4;187,189,201,199;,
 4;189,190,202,201;,
 4;190,191,203,202;,
 4;191,192,204,203;,
 4;192,193,205,204;,
 4;193,194,206,205;,
 4;194,195,207,206;,
 4;195,196,208,207;,
 4;196,197,209,208;,
 4;197,198,210,209;,
 4;200,199,211,212;,
 4;199,201,213,211;,
 4;201,202,214,213;,
 4;202,203,215,214;,
 4;203,204,216,215;,
 4;204,205,217,216;,
 4;205,206,218,217;,
 4;206,207,219,218;,
 4;207,208,220,219;,
 4;208,209,221,220;,
 4;209,210,222,221;,
 4;212,211,223,224;,
 4;211,213,225,223;,
 4;213,214,226,225;,
 4;214,215,227,226;,
 4;215,216,228,227;,
 4;216,217,229,228;,
 4;218,219,230,231;,
 4;219,220,232,230;,
 4;220,221,233,232;,
 4;221,222,234,233;,
 3;235,142,236;,
 4;235,236,156,154;,
 3;235,154,237;,
 4;235,237,141,142;,
 4;238,218,231,239;,
 4;238,239,229,217;;
 
 MeshMaterialList {
  1;
  283;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.426400;0.659200;0.752800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  176;
  -0.340045;-0.568105;0.749417;,
  -0.204240;-0.556103;0.805627;,
  -0.210727;0.203940;0.956035;,
  -0.109502;0.199061;0.973850;,
  0.110691;0.804661;0.583325;,
  0.061651;0.586033;0.807939;,
  0.425053;0.857066;0.291149;,
  0.107173;0.985705;0.130002;,
  0.054238;0.998466;-0.011134;,
  0.440918;0.897463;0.012295;,
  0.334807;0.797721;-0.501542;,
  0.503757;0.856892;-0.109382;,
  0.166129;0.874887;-0.454944;,
  0.156577;0.982915;-0.096755;,
  0.096853;-0.393409;-0.914248;,
  0.260694;0.193279;-0.945876;,
  0.004896;-0.588212;-0.808692;,
  -0.020792;0.310290;-0.950415;,
  0.136830;-0.870979;-0.471882;,
  -0.053885;-0.960542;-0.272864;,
  -0.289830;-0.956969;-0.014414;,
  -0.058311;-0.988901;-0.136654;,
  -0.079060;-0.965050;0.249856;,
  -0.361811;-0.924528;0.119754;,
  -0.295571;0.741992;0.601735;,
  -0.263959;0.066619;0.962230;,
  -0.192144;-0.679493;0.708075;,
  -0.239098;0.963310;0.121925;,
  -0.222414;0.974910;-0.009112;,
  -0.155370;0.985427;-0.069242;,
  -0.049085;0.892300;-0.448767;,
  -0.013162;-0.498957;-0.866527;,
  0.138121;0.285688;-0.948317;,
  -0.178339;-0.983914;-0.010426;,
  -0.125304;-0.958478;-0.256163;,
  -0.159109;-0.974816;0.156264;,
  0.373454;0.085256;-0.923723;,
  -0.174677;-0.694213;-0.698252;,
  0.012935;-0.936559;0.350271;,
  -0.272736;0.033254;0.961514;,
  0.084520;0.913252;0.398532;,
  0.346388;0.938010;0.012344;,
  0.413258;0.895989;-0.162545;,
  0.531022;0.582806;-0.615103;,
  0.500567;0.139772;-0.854339;,
  -0.435510;-0.419049;0.796699;,
  -0.376183;0.361292;-0.853203;,
  -0.317299;-0.300626;-0.899414;,
  -0.475792;-0.771290;-0.422770;,
  -0.437263;-0.898084;-0.047393;,
  -0.456887;-0.885685;0.082561;,
  -0.532391;-0.706189;0.466752;,
  -0.075659;-0.034763;0.996528;,
  -0.507572;0.636232;0.581016;,
  -0.390120;0.915273;0.100409;,
  -0.301473;0.951567;0.060292;,
  -0.287365;0.956329;-0.053441;,
  -0.405593;0.810852;-0.421916;,
  -0.633078;0.003317;-0.774081;,
  -0.642254;-0.385150;-0.662699;,
  -0.611890;-0.741905;-0.274169;,
  -0.543792;-0.837160;-0.058761;,
  -0.664193;-0.702428;0.255817;,
  -0.750588;-0.462648;0.471778;,
  -0.717967;0.055111;0.693892;,
  -0.576089;0.450177;0.682248;,
  -0.490610;0.819321;0.296674;,
  -0.375422;0.925628;0.047661;,
  -0.487881;0.830983;-0.267282;,
  -0.591898;0.547392;-0.591623;,
  -0.685312;-0.013314;-0.728128;,
  -0.648985;-0.477829;-0.592029;,
  -0.588474;-0.747435;-0.308285;,
  -0.562519;-0.826767;0.005389;,
  -0.586814;-0.743427;0.320882;,
  -0.647723;-0.462297;0.605588;,
  -0.685316;0.013317;0.728124;,
  -0.648987;0.477827;0.592028;,
  -0.588474;0.747435;0.308285;,
  -0.562507;0.826775;-0.005390;,
  -0.586795;0.743440;-0.320887;,
  -0.647708;0.462316;-0.605589;,
  -0.872339;-0.014970;-0.488672;,
  -0.857144;-0.342688;-0.384538;,
  -0.785281;-0.582546;-0.209701;,
  -0.790122;-0.612897;0.008015;,
  -0.809179;-0.538596;0.234825;,
  -0.850554;-0.317791;0.419006;,
  -0.872341;0.014971;0.488669;,
  -0.848638;0.339253;0.405858;,
  -0.808034;0.547112;0.218519;,
  -0.790133;0.612883;-0.008010;,
  -0.809186;0.538587;-0.234824;,
  -0.850550;0.317802;-0.419007;,
  -0.963277;-0.027391;-0.267108;,
  -0.963508;-0.167842;-0.208522;,
  -0.933168;-0.332076;-0.137564;,
  -0.933130;-0.359061;0.018523;,
  -0.942143;-0.301489;0.146533;,
  -0.957351;-0.161573;0.239525;,
  -0.963275;0.027394;0.267115;,
  -0.953499;0.207241;0.218839;,
  -0.938572;0.325959;0.113280;,
  -0.933129;0.359064;-0.018521;,
  -0.942140;0.301495;-0.146534;,
  -0.957351;0.161578;-0.239523;,
  -1.000000;0.000002;-0.000000;,
  1.000000;-0.000000;-0.000001;,
  0.951247;-0.000005;-0.308429;,
  0.951249;-0.166746;-0.259464;,
  0.951249;-0.280549;-0.128131;,
  0.951249;-0.305287;0.043886;,
  0.951248;-0.233089;0.201981;,
  0.951248;-0.086887;0.295937;,
  0.951248;0.086893;0.295935;,
  0.951249;0.233089;0.201979;,
  0.951251;0.305279;0.043887;,
  0.951249;0.280552;-0.128124;,
  0.951250;0.166746;-0.259459;,
  0.809591;-0.000004;-0.586995;,
  0.809593;-0.317351;-0.493809;,
  0.809590;-0.533946;-0.243855;,
  0.809592;-0.581018;0.083538;,
  0.809589;-0.443616;0.384410;,
  0.809593;-0.165373;0.563215;,
  0.809592;0.165373;0.563216;,
  0.809592;0.443614;0.384406;,
  0.809594;0.581016;0.083536;,
  0.809590;0.533949;-0.243849;,
  0.809593;0.317350;-0.493810;,
  0.588552;-0.000002;-0.808459;,
  0.588548;-0.437090;-0.680120;,
  0.588543;-0.735403;-0.335858;,
  0.588547;-0.800233;0.115061;,
  0.588541;-0.610991;0.529443;,
  0.588545;-0.227774;0.775715;,
  0.588549;0.227767;0.775714;,
  0.588549;0.610992;0.529432;,
  0.588538;0.800241;0.115052;,
  0.588531;0.735413;-0.335855;,
  0.588544;0.437090;-0.680124;,
  0.495675;0.064123;-0.866138;,
  0.526464;-0.495026;-0.691220;,
  0.339849;-0.891835;-0.298550;,
  0.270895;-0.960377;0.065508;,
  0.441472;-0.786168;0.432484;,
  0.660388;-0.366532;0.655394;,
  0.730390;0.147541;0.666905;,
  0.532353;0.730159;0.428332;,
  0.395719;0.912993;0.099246;,
  0.410747;0.851986;-0.324664;,
  0.469791;0.520214;-0.713214;,
  0.618542;0.254651;-0.743343;,
  0.112775;-0.931788;-0.345041;,
  -0.075982;-0.954509;-0.288340;,
  0.063566;-0.991930;-0.109704;,
  -0.882821;-0.347828;0.315661;,
  -0.487733;-0.189899;0.852088;,
  -0.033834;0.009197;0.999385;,
  0.316887;0.905303;0.282860;,
  0.082724;0.993591;0.077032;,
  0.181129;0.957448;-0.224691;,
  0.398869;0.707717;-0.583130;,
  -0.675461;-0.724316;0.138274;,
  -0.675452;-0.724325;0.138267;,
  0.839401;0.437267;0.322807;,
  0.237139;0.618234;0.749367;,
  -0.675456;-0.724321;0.138270;,
  -0.971415;-0.208738;0.113052;,
  -0.949645;-0.296805;-0.100403;,
  0.602189;0.035049;-0.797584;,
  0.798554;-0.038817;-0.600670;,
  -0.942934;-0.023963;0.332117;,
  0.412734;-0.871865;0.263633;,
  0.804889;-0.447674;0.389542;,
  0.915500;0.027729;0.401362;;
  283;
  3;45,39,0;,
  3;39,2,0;,
  3;0,2,1;,
  3;39,166,2;,
  3;1,2,3;,
  3;2,5,3;,
  3;3,5,4;,
  3;2,166,5;,
  3;166,40,5;,
  3;40,6,5;,
  3;5,6,4;,
  3;40,41,6;,
  3;4,6,7;,
  3;6,9,7;,
  3;7,9,8;,
  3;6,41,9;,
  3;43,10,42;,
  3;10,11,42;,
  3;42,11,41;,
  3;10,12,11;,
  3;41,11,9;,
  3;11,13,9;,
  3;9,13,8;,
  3;11,12,13;,
  3;36,14,44;,
  3;14,15,44;,
  3;44,15,43;,
  3;14,16,15;,
  3;43,15,10;,
  3;15,17,10;,
  3;10,17,12;,
  3;15,16,17;,
  3;36,37,14;,
  3;37,18,14;,
  3;14,18,16;,
  3;37,155,18;,
  3;16,18,19;,
  3;18,21,19;,
  3;19,21,20;,
  3;18,155,21;,
  3;45,0,38;,
  3;0,22,38;,
  3;38,22,155;,
  3;0,1,22;,
  3;155,22,21;,
  3;22,23,21;,
  3;21,23,20;,
  3;22,1,23;,
  3;4,24,3;,
  3;24,25,3;,
  3;3,25,1;,
  3;24,53,25;,
  3;1,25,26;,
  3;25,52,26;,
  3;26,52,51;,
  3;25,53,52;,
  3;4,7,24;,
  3;7,27,24;,
  3;24,27,53;,
  3;7,8,27;,
  3;53,27,54;,
  3;27,28,54;,
  3;54,28,55;,
  3;27,8,28;,
  3;8,13,28;,
  3;13,29,28;,
  3;28,29,55;,
  3;13,12,29;,
  3;55,29,56;,
  3;29,30,56;,
  3;56,30,57;,
  3;29,12,30;,
  3;16,31,17;,
  3;31,32,17;,
  3;17,32,12;,
  3;31,47,32;,
  3;12,32,30;,
  3;32,46,30;,
  3;30,46,57;,
  3;32,47,46;,
  3;20,33,19;,
  3;33,34,19;,
  3;19,34,16;,
  3;33,49,34;,
  3;16,34,31;,
  3;34,48,31;,
  3;31,48,47;,
  3;34,49,48;,
  3;1,26,23;,
  3;26,35,23;,
  3;23,35,20;,
  3;26,51,35;,
  3;20,35,33;,
  3;35,50,33;,
  3;33,50,49;,
  3;35,51,50;,
  3;94,95,106;,
  3;95,96,106;,
  3;96,97,106;,
  3;97,98,106;,
  3;98,99,106;,
  3;99,100,106;,
  3;100,101,106;,
  3;101,102,106;,
  3;102,103,106;,
  3;103,104,106;,
  3;104,105,106;,
  3;105,94,106;,
  3;156,45,168;,
  3;156,168,169;,
  3;156,157,45;,
  3;154,155,37;,
  3;154,37,153;,
  3;157,158,45;,
  3;158,166,39;,
  3;158,39,45;,
  3;170,37,36;,
  3;170,36,152;,
  3;159,40,166;,
  3;171,171,171;,
  3;152,36,44;,
  3;160,41,40;,
  3;160,40,159;,
  3;152,44,43;,
  3;152,43,162;,
  3;161,42,41;,
  3;161,41,160;,
  3;162,43,42;,
  3;162,42,161;,
  3;47,59,58;,
  3;47,58,46;,
  3;48,60,59;,
  3;48,59,47;,
  3;49,61,60;,
  3;49,60,48;,
  3;50,62,61;,
  3;50,61,49;,
  3;51,63,62;,
  3;51,62,50;,
  3;172,64,63;,
  3;172,63,51;,
  3;53,65,64;,
  3;53,64,172;,
  3;53,54,66;,
  3;53,66,65;,
  3;55,67,66;,
  3;55,66,54;,
  3;56,68,67;,
  3;56,67,55;,
  3;57,69,68;,
  3;57,68,56;,
  3;46,58,69;,
  3;46,69,57;,
  3;59,71,70;,
  3;59,70,58;,
  3;60,72,71;,
  3;60,71,59;,
  3;61,73,72;,
  3;61,72,60;,
  3;62,74,73;,
  3;62,73,61;,
  3;63,75,74;,
  3;63,74,62;,
  3;64,76,75;,
  3;64,75,63;,
  3;65,77,76;,
  3;65,76,64;,
  3;66,78,77;,
  3;66,77,65;,
  3;67,79,78;,
  3;67,78,66;,
  3;68,80,79;,
  3;68,79,67;,
  3;69,81,80;,
  3;69,80,68;,
  3;58,70,81;,
  3;58,81,69;,
  3;71,83,82;,
  3;71,82,70;,
  3;72,84,83;,
  3;72,83,71;,
  3;73,85,84;,
  3;73,84,72;,
  3;75,87,86;,
  3;75,86,74;,
  3;76,88,87;,
  3;76,87,75;,
  3;77,89,88;,
  3;77,88,76;,
  3;78,90,89;,
  3;78,89,77;,
  3;79,91,90;,
  3;79,90,78;,
  3;80,92,91;,
  3;80,91,79;,
  3;81,93,92;,
  3;81,92,80;,
  3;70,82,93;,
  3;70,93,81;,
  3;83,95,94;,
  3;83,94,82;,
  3;83,84,96;,
  3;83,96,95;,
  3;85,97,96;,
  3;85,96,84;,
  3;86,98,97;,
  3;86,97,85;,
  3;87,99,98;,
  3;87,98,86;,
  3;88,100,99;,
  3;88,99,87;,
  3;89,101,100;,
  3;89,100,88;,
  3;90,102,101;,
  3;90,101,89;,
  3;91,103,102;,
  3;91,102,90;,
  3;92,104,103;,
  3;92,103,91;,
  3;93,105,104;,
  3;93,104,92;,
  3;82,94,105;,
  3;82,105,93;,
  3;107,109,108;,
  3;107,110,109;,
  3;107,111,110;,
  3;107,112,111;,
  3;107,113,112;,
  3;107,114,113;,
  3;107,115,114;,
  3;107,116,115;,
  3;107,117,116;,
  3;107,118,117;,
  3;107,108,118;,
  4;108,109,120,119;,
  4;109,110,121,120;,
  4;110,111,122,121;,
  4;111,112,123,122;,
  4;112,113,124,123;,
  4;113,114,125,124;,
  4;114,115,126,125;,
  4;115,116,127,126;,
  4;116,117,128,127;,
  4;117,118,129,128;,
  4;118,108,119,129;,
  4;119,120,131,130;,
  4;120,121,132,131;,
  4;121,122,133,132;,
  4;122,123,134,133;,
  4;123,124,135,134;,
  4;124,125,136,135;,
  4;125,126,137,136;,
  4;126,127,138,137;,
  4;127,128,139,138;,
  4;128,129,140,139;,
  4;129,119,130,140;,
  4;130,131,142,141;,
  4;131,132,143,142;,
  4;132,133,144,143;,
  4;133,134,145,144;,
  4;134,135,146,145;,
  4;135,136,147,146;,
  4;136,137,148,147;,
  4;137,138,149,148;,
  4;138,139,150,149;,
  4;139,140,151,150;,
  4;140,130,141,151;,
  4;141,142,170,152;,
  4;142,143,154,153;,
  4;143,144,155,154;,
  4;144,145,173,155;,
  4;145,146,174,173;,
  4;146,147,175,174;,
  4;148,149,160,159;,
  4;149,150,161,160;,
  4;150,151,162,161;,
  4;151,141,152,162;,
  3;167,74,164;,
  4;167,164,86,85;,
  3;167,85,163;,
  4;167,163,73,74;,
  4;165,148,159,166;,
  4;165,166,175,147;;
 }
 MeshTextureCoords {
  240;
  0.878240;0.872360;,
  0.878230;0.811580;,
  0.876620;0.873680;,
  0.876610;0.812900;,
  0.875000;0.875000;,
  0.878220;0.750800;,
  0.875000;0.812500;,
  0.876610;0.750400;,
  0.875000;0.750000;,
  0.817740;0.750470;,
  0.816130;0.750070;,
  0.757250;0.750140;,
  0.812500;0.750000;,
  0.753630;0.750070;,
  0.750000;0.750000;,
  0.630500;0.752250;,
  0.627750;0.751120;,
  0.693880;0.751200;,
  0.691130;0.750070;,
  0.625000;0.750000;,
  0.687500;0.750000;,
  0.659270;0.868550;,
  0.642140;0.871780;,
  0.644890;0.810400;,
  0.627750;0.813620;,
  0.625000;0.875000;,
  0.625000;0.812500;,
  0.712100;0.871260;,
  0.694970;0.874480;,
  0.764930;0.873960;,
  0.687500;0.875000;,
  0.757470;0.874480;,
  0.750000;0.875000;,
  0.821580;0.873160;,
  0.819970;0.874480;,
  0.812500;0.875000;,
  0.875000;0.750000;,
  0.875000;0.812500;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;0.812500;,
  0.875000;0.875000;,
  0.812500;0.750000;,
  0.812500;0.750000;,
  0.750000;0.750000;,
  0.750000;0.750000;,
  0.687500;0.750000;,
  0.687500;0.750000;,
  0.625000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;0.812500;,
  0.625000;0.875000;,
  0.625000;0.812500;,
  0.750000;0.875000;,
  0.687500;0.875000;,
  0.750000;0.875000;,
  0.687500;0.875000;,
  0.812500;0.875000;,
  0.812500;0.875000;,
  0.000000;0.900000;,
  0.083330;0.900000;,
  0.041670;1.000000;,
  0.166670;0.900000;,
  0.125000;1.000000;,
  0.250000;0.900000;,
  0.208330;1.000000;,
  0.333330;0.900000;,
  0.291670;1.000000;,
  0.416670;0.900000;,
  0.375000;1.000000;,
  0.500000;0.900000;,
  0.458330;1.000000;,
  0.583330;0.900000;,
  0.541670;1.000000;,
  0.666670;0.900000;,
  0.625000;1.000000;,
  0.750000;0.900000;,
  0.708330;1.000000;,
  0.833330;0.900000;,
  0.791670;1.000000;,
  0.916670;0.900000;,
  0.875000;1.000000;,
  1.000000;0.900000;,
  0.958330;1.000000;,
  0.333330;0.533860;,
  0.333330;0.666670;,
  0.250000;0.666670;,
  0.250000;0.533860;,
  0.416670;0.333330;,
  0.416670;0.533860;,
  0.166670;0.533860;,
  0.166670;0.666670;,
  0.083330;0.666670;,
  0.083330;0.533860;,
  0.500000;0.533860;,
  0.500000;0.666670;,
  0.416670;0.666670;,
  0.000000;0.666670;,
  0.000000;0.533860;,
  0.583330;0.533860;,
  0.583330;0.666670;,
  1.000000;0.533860;,
  1.000000;0.666670;,
  0.916670;0.666670;,
  0.666670;0.533860;,
  0.666670;0.666670;,
  0.916670;0.533860;,
  0.833330;0.666670;,
  0.833330;0.533860;,
  0.750000;0.533860;,
  0.750000;0.666670;,
  0.083330;0.500000;,
  0.083330;0.600000;,
  0.000000;0.600000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.600000;,
  0.250000;0.500000;,
  0.250000;0.600000;,
  0.333330;0.500000;,
  0.333330;0.600000;,
  0.416670;0.500000;,
  0.416670;0.600000;,
  0.500000;0.500000;,
  0.500000;0.600000;,
  0.583330;0.500000;,
  0.583330;0.600000;,
  0.666670;0.500000;,
  0.666670;0.600000;,
  0.750000;0.500000;,
  0.750000;0.600000;,
  0.833330;0.500000;,
  0.833330;0.600000;,
  0.916670;0.500000;,
  0.916670;0.600000;,
  1.000000;0.500000;,
  1.000000;0.600000;,
  0.083330;0.700000;,
  0.000000;0.700000;,
  0.166670;0.700000;,
  0.250000;0.700000;,
  0.333330;0.700000;,
  0.416670;0.700000;,
  0.500000;0.700000;,
  0.583330;0.700000;,
  0.666670;0.700000;,
  0.750000;0.700000;,
  0.833330;0.700000;,
  0.916670;0.700000;,
  1.000000;0.700000;,
  0.083330;0.800000;,
  0.000000;0.800000;,
  0.166670;0.800000;,
  0.250000;0.800000;,
  0.416670;0.800000;,
  0.333330;0.800000;,
  0.500000;0.800000;,
  0.583330;0.800000;,
  0.666670;0.800000;,
  0.750000;0.800000;,
  0.833330;0.800000;,
  0.916670;0.800000;,
  1.000000;0.800000;,
  0.045450;0.000000;,
  0.090910;0.100000;,
  0.000000;0.100000;,
  0.136360;0.000000;,
  0.181820;0.100000;,
  0.227270;0.000000;,
  0.272730;0.100000;,
  0.318180;0.000000;,
  0.363640;0.100000;,
  0.409090;0.000000;,
  0.454550;0.100000;,
  0.500000;0.000000;,
  0.545450;0.100000;,
  0.590910;0.000000;,
  0.636360;0.100000;,
  0.681820;0.000000;,
  0.727270;0.100000;,
  0.772730;0.000000;,
  0.818180;0.100000;,
  0.863640;0.000000;,
  0.909090;0.100000;,
  0.954550;0.000000;,
  1.000000;0.100000;,
  0.090910;0.200000;,
  0.000000;0.200000;,
  0.181820;0.200000;,
  0.272730;0.200000;,
  0.363640;0.200000;,
  0.454550;0.200000;,
  0.545450;0.200000;,
  0.636360;0.200000;,
  0.727270;0.200000;,
  0.818180;0.200000;,
  0.909090;0.200000;,
  1.000000;0.200000;,
  0.090910;0.300000;,
  0.000000;0.300000;,
  0.181820;0.300000;,
  0.272730;0.300000;,
  0.363640;0.300000;,
  0.454550;0.300000;,
  0.545450;0.300000;,
  0.636360;0.300000;,
  0.727270;0.300000;,
  0.818180;0.300000;,
  0.909090;0.300000;,
  1.000000;0.300000;,
  0.090910;0.400000;,
  0.000000;0.400000;,
  0.181820;0.400000;,
  0.272730;0.400000;,
  0.363640;0.400000;,
  0.454550;0.400000;,
  0.545450;0.400000;,
  0.636360;0.400000;,
  0.727270;0.400000;,
  0.818180;0.400000;,
  0.909090;0.400000;,
  1.000000;0.400000;,
  0.090910;0.500000;,
  0.000000;0.500000;,
  0.181820;0.500000;,
  0.272730;0.500000;,
  0.363640;0.500000;,
  0.454550;0.500000;,
  0.545450;0.500000;,
  0.727270;0.500000;,
  0.636360;0.500000;,
  0.818180;0.500000;,
  0.909090;0.500000;,
  1.000000;0.500000;,
  0.281120;0.762660;,
  0.333330;0.768370;,
  0.250000;0.757810;,
  0.586000;0.400000;,
  0.596210;0.500000;;
 }
}
