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
 163;
 1.55792;-0.17903;1.56064;,
 1.19993;1.22618;2.04277;,
 0.29490;1.22618;2.83554;,
 1.05355;-0.17903;2.32370;,
 -0.78960;1.22618;2.13760;,
 -0.05372;-0.17903;1.87920;,
 -2.26238;1.22618;2.44425;,
 -1.17459;-0.17903;2.30999;,
 -2.48776;1.22618;1.47850;,
 -1.65515;-0.17903;1.54087;,
 -3.96571;1.22618;1.18189;,
 -2.96439;-0.17903;1.47485;,
 -3.24589;1.22618;0.31724;,
 -2.63468;-0.17903;0.67488;,
 -4.16449;1.22618;-0.46933;,
 -3.63220;-0.17903;0.13727;,
 -2.77441;1.22618;-0.90262;,
 -2.61817;-0.17903;-0.38798;,
 -2.78280;1.22618;-1.87871;,
 -2.92295;-0.17903;-1.19184;,
 -1.25342;1.22618;-2.40518;,
 -1.61190;-0.17903;-1.96275;,
 -0.34839;1.22618;-2.50792;,
 -1.10753;-0.17903;-2.00480;,
 0.73611;1.22618;-2.50001;,
 -0.00027;-0.17903;-2.28131;,
 2.20889;1.22618;-2.11662;,
 1.12060;-0.17903;-1.99109;,
 2.43451;1.22658;-1.15098;,
 1.59836;-0.17560;-1.22172;,
 3.91236;1.22277;-0.85389;,
 2.90757;-0.17996;-1.15528;,
 3.19226;1.22520;0.01053;,
 2.57760;-0.17830;-0.35543;,
 4.11062;1.22316;0.79739;,
 3.57495;-0.18128;0.18251;,
 2.72040;1.22713;1.23025;,
 2.56075;-0.17750;0.70743;,
 2.72931;1.22618;2.20633;,
 2.86896;-0.17903;1.51074;,
 1.19993;1.22618;2.04277;,
 1.55792;-0.17903;1.56064;,
 1.14190;8.38379;1.88938;,
 -0.02670;8.91014;-1.10639;,
 0.29920;8.38379;2.82997;,
 -0.72534;8.38379;2.02292;,
 -2.10546;8.38379;2.39931;,
 -2.32573;8.38379;1.26834;,
 -3.71612;8.61195;0.93675;,
 -3.04797;7.84288;-0.08615;,
 -3.91754;8.61195;-0.99906;,
 -2.61619;8.29012;-1.52317;,
 -2.63280;7.84288;-2.66871;,
 -1.19531;7.84288;-3.29800;,
 -0.35261;7.84288;-3.43444;,
 0.67193;7.84288;-3.43154;,
 2.05205;7.84288;-3.00377;,
 2.27232;8.29012;-1.87281;,
 3.66271;8.61195;-1.54121;,
 2.99456;8.38379;-0.51831;,
 3.86413;8.61195;0.39460;,
 2.56278;8.38379;0.91872;,
 2.57939;8.38379;2.06425;,
 1.19993;1.22618;2.04277;,
 1.32744;2.53974;2.06019;,
 0.14747;2.53974;2.94139;,
 0.29490;1.22618;2.83554;,
 -1.12966;2.53974;2.01279;,
 -0.78960;1.22618;2.13760;,
 -2.96818;2.53974;2.26245;,
 -2.26238;1.22618;2.44425;,
 -3.16545;2.53974;1.08113;,
 -2.48776;1.22618;1.47850;,
 -4.96026;2.53974;0.60389;,
 -3.96571;1.22618;1.18189;,
 -4.00233;2.53974;-0.37892;,
 -3.24589;1.22618;0.31724;,
 -5.06788;2.53974;-1.40078;,
 -4.16449;1.22618;-0.46933;,
 -3.32064;2.53974;-1.80968;,
 -2.77441;1.22618;-0.90262;,
 -3.24993;2.53974;-2.98584;,
 -2.78280;1.22618;-1.87871;,
 -1.38076;2.53974;-3.43293;,
 -1.25342;1.22618;-2.40518;,
 -0.20079;2.53974;-3.54585;,
 -0.34839;1.22618;-2.50792;,
 1.07634;2.53974;-3.38553;,
 0.73611;1.22618;-2.50001;,
 2.91485;2.53974;-2.86692;,
 2.20889;1.22618;-2.11662;,
 3.11648;2.54003;-1.68651;,
 2.43451;1.22658;-1.15098;,
 4.91114;2.53602;-1.20871;,
 3.91236;1.22277;-0.85389;,
 3.95288;2.53877;-0.22619;,
 3.19226;1.22520;0.01053;,
 5.01809;2.53677;0.79599;,
 4.11062;1.22316;0.79739;,
 3.27072;2.54109;1.20435;,
 2.72040;1.22713;1.23025;,
 3.19661;2.53974;2.38137;,
 2.72931;1.22618;2.20633;,
 1.94593;4.00667;2.40584;,
 0.56120;4.00667;3.59169;,
 -1.15155;4.00667;2.60489;,
 -3.43682;4.00667;3.09771;,
 -3.81938;4.00667;1.69351;,
 -5.31821;4.77575;1.30508;,
 -5.03853;4.77575;0.01983;,
 -5.63311;4.77575;-1.10149;,
 -4.34333;4.00667;-1.77687;,
 -4.38806;4.00667;-3.20278;,
 -1.99933;4.00667;-3.80143;,
 -0.61461;4.00667;-4.19614;,
 1.09815;4.00667;-4.00047;,
 3.38340;4.00667;-3.70218;,
 3.76597;4.00667;-2.29797;,
 5.26480;4.77575;-1.90954;,
 4.98512;4.77575;-0.62429;,
 5.57970;4.77575;0.49703;,
 4.28993;4.00667;1.17240;,
 4.33466;4.00667;2.59831;,
 2.13776;5.57585;2.34472;,
 1.25686;5.57585;3.98045;,
 -0.48436;5.57585;3.22661;,
 -2.45854;5.57585;4.26884;,
 -3.07584;5.57585;2.76060;,
 -4.26686;6.34493;2.81125;,
 -4.22315;6.34493;1.12470;,
 -4.91145;6.34493;0.16441;,
 -4.38937;6.34493;-1.05624;,
 -4.25385;6.34493;-2.66067;,
 -2.19116;5.57585;-4.22136;,
 -1.23012;5.57585;-4.58490;,
 0.40238;5.57585;-4.63524;,
 2.25327;5.57585;-4.87331;,
 2.83202;5.57585;-4.35324;,
 4.21346;6.34493;-3.41571;,
 4.74575;6.34493;-1.72916;,
 4.85804;6.34493;-0.76887;,
 3.90455;6.34493;0.45178;,
 4.20044;6.34493;2.05620;,
 1.89923;7.14706;2.20166;,
 0.98097;7.14706;3.66833;,
 -0.49953;7.14706;2.91958;,
 -2.22069;7.14706;3.81063;,
 -2.71769;7.14706;2.40688;,
 -3.97663;7.91614;2.38197;,
 -3.90798;7.91614;0.85939;,
 -4.51637;7.91614;-0.07197;,
 -4.47862;7.91614;-1.13180;,
 -3.85114;7.91614;-2.61386;,
 -1.95264;7.14706;-3.61028;,
 -1.03438;7.14706;-4.27278;,
 0.44612;7.14706;-4.32820;,
 2.16727;7.14706;-4.41509;,
 3.29205;7.14706;-4.15511;,
 4.53090;7.91614;-2.98643;,
 4.07609;7.91614;-1.46385;,
 4.46296;7.91614;-0.53250;,
 3.56234;7.91614;0.52734;,
 3.79773;7.91614;2.00940;;
 
 158;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,32,33;,
 4;33,32,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;39,38,40,41;,
 3;42,43,44;,
 3;44,43,45;,
 3;45,43,46;,
 3;46,43,47;,
 3;47,43,48;,
 3;48,43,49;,
 3;49,43,50;,
 3;50,43,51;,
 3;51,43,52;,
 3;52,43,53;,
 3;53,43,54;,
 3;54,43,55;,
 3;55,43,56;,
 3;56,43,57;,
 3;57,43,58;,
 3;58,43,59;,
 3;59,43,60;,
 3;60,43,61;,
 3;61,43,62;,
 3;62,43,42;,
 4;63,64,65,66;,
 4;66,65,67,68;,
 4;68,67,69,70;,
 4;70,69,71,72;,
 4;72,71,73,74;,
 4;74,73,75,76;,
 4;76,75,77,78;,
 4;78,77,79,80;,
 4;80,79,81,82;,
 4;82,81,83,84;,
 4;84,83,85,86;,
 4;86,85,87,88;,
 4;88,87,89,90;,
 4;90,89,91,92;,
 4;92,91,93,94;,
 4;94,93,95,96;,
 4;96,95,97,98;,
 4;98,97,99,100;,
 4;100,99,101,102;,
 4;102,101,64,63;,
 4;64,103,104,65;,
 4;65,104,105,67;,
 4;67,105,106,69;,
 4;69,106,107,71;,
 4;71,107,108,73;,
 4;73,108,109,75;,
 4;75,109,110,77;,
 4;77,110,111,79;,
 4;79,111,112,81;,
 4;81,112,113,83;,
 4;83,113,114,85;,
 4;85,114,115,87;,
 4;87,115,116,89;,
 4;89,116,117,91;,
 4;91,117,118,93;,
 4;93,118,119,95;,
 4;95,119,120,97;,
 4;97,120,121,99;,
 4;99,121,122,101;,
 4;101,122,103,64;,
 4;103,123,124,104;,
 4;104,124,125,105;,
 4;105,125,126,106;,
 4;106,126,127,107;,
 4;107,127,128,108;,
 4;108,128,129,109;,
 4;109,129,130,110;,
 4;110,130,131,111;,
 4;111,131,132,112;,
 4;112,132,133,113;,
 4;113,133,134,114;,
 4;114,134,135,115;,
 4;115,135,136,116;,
 4;116,136,137,117;,
 4;117,137,138,118;,
 4;118,138,139,119;,
 4;119,139,140,120;,
 4;120,140,141,121;,
 4;121,141,142,122;,
 4;122,142,123,103;,
 4;123,143,144,124;,
 4;124,144,145,125;,
 4;125,145,146,126;,
 4;126,146,147,127;,
 4;127,147,148,128;,
 4;128,148,149,129;,
 4;129,149,150,130;,
 4;130,150,151,131;,
 4;131,151,152,132;,
 4;132,152,153,133;,
 4;133,153,154,134;,
 4;134,154,155,135;,
 4;135,155,156,136;,
 4;136,156,157,137;,
 4;137,157,158,138;,
 4;138,158,159,139;,
 4;139,159,160,140;,
 4;140,160,161,141;,
 4;141,161,162,142;,
 4;142,162,143,123;,
 4;143,42,44,144;,
 4;144,44,45,145;,
 4;145,45,46,146;,
 4;146,46,47,147;,
 4;147,47,48,148;,
 4;148,48,49,149;,
 4;149,49,50,150;,
 4;150,50,51,151;,
 4;151,51,52,152;,
 4;152,52,53,153;,
 4;153,53,54,154;,
 4;154,54,55,155;,
 4;155,55,56,156;,
 4;156,56,57,157;,
 4;157,57,58,158;,
 4;158,58,59,159;,
 4;159,59,60,160;,
 4;160,60,61,161;,
 4;161,61,62,162;,
 4;162,62,42,143;,
 3;3,5,41;,
 3;39,41,37;,
 3;35,37,33;,
 3;31,33,29;,
 3;15,17,13;,
 3;11,13,9;,
 3;7,9,5;,
 3;19,21,17;,
 3;21,23,17;,
 3;27,29,25;,
 3;25,29,23;,
 3;23,29,17;,
 3;29,33,17;,
 3;33,37,17;,
 3;37,41,17;,
 3;41,5,17;,
 3;17,5,13;,
 3;13,5,9;;
 
 MeshMaterialList {
  1;
  158;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.792000;0.800000;0.536000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  199;
  0.338266;-0.115749;0.933905;,
  0.693792;0.008676;0.720124;,
  -0.146287;-0.090575;0.985087;,
  0.225362;0.107994;0.968271;,
  -0.836531;-0.488000;0.249143;,
  -0.173677;0.124442;0.976909;,
  -0.661568;-0.574560;-0.481880;,
  -0.619445;0.040927;0.783973;,
  -0.279247;-0.526403;-0.803070;,
  -0.983470;-0.160992;0.082876;,
  -0.202458;-0.469149;-0.859599;,
  -0.060906;-0.430999;-0.900295;,
  0.101572;-0.420999;-0.901356;,
  0.578589;-0.534263;-0.616277;,
  0.668441;-0.549511;-0.501223;,
  0.169496;-0.199799;-0.965066;,
  0.726299;-0.422951;0.541851;,
  0.604318;-0.202756;-0.770513;,
  0.307317;-0.276089;0.910676;,
  0.984632;-0.153511;-0.083277;,
  0.255781;-0.174427;0.950869;,
  0.608477;-0.242521;0.755605;,
  -0.209352;-0.167846;0.963327;,
  0.169538;-0.120423;0.978139;,
  -0.762062;-0.463353;0.452290;,
  -0.280794;-0.099812;0.954564;,
  -0.754663;-0.408835;-0.513164;,
  -0.727676;-0.161392;0.666664;,
  -0.289994;-0.367409;-0.883694;,
  -0.872616;-0.488068;-0.018177;,
  -0.175742;-0.498467;-0.848908;,
  -0.023087;-0.501783;-0.864685;,
  0.140973;-0.505533;-0.851212;,
  0.597141;-0.561219;-0.573110;,
  0.628551;-0.503041;-0.593189;,
  0.258324;-0.415048;-0.872355;,
  0.795642;-0.239863;0.556255;,
  0.679830;-0.397209;-0.616487;,
  0.304319;-0.098634;0.947450;,
  0.876253;-0.481470;0.019190;,
  0.332311;-0.194334;0.922932;,
  0.665185;-0.356828;0.655898;,
  -0.143169;-0.367968;0.918750;,
  0.224416;-0.493247;0.840443;,
  -0.713281;-0.295609;0.635488;,
  -0.330446;-0.428246;0.841077;,
  -0.985902;0.166630;-0.015189;,
  -0.815304;-0.166542;0.554566;,
  -0.751429;0.169882;-0.637570;,
  -0.954501;-0.297506;-0.020464;,
  -0.278738;-0.262523;-0.923789;,
  -0.082165;-0.345236;-0.934913;,
  0.082240;-0.404444;-0.910857;,
  0.564284;-0.382064;-0.731854;,
  0.707870;-0.326810;-0.626191;,
  0.436246;-0.424589;-0.793356;,
  0.995889;0.078094;0.045905;,
  0.882319;-0.153183;-0.445026;,
  0.426681;0.235535;0.873193;,
  0.960511;-0.273764;-0.049717;,
  0.478428;0.044894;0.876978;,
  0.826352;-0.030856;0.562308;,
  -0.035861;-0.100094;0.994332;,
  0.403674;-0.213814;0.889568;,
  -0.906275;0.268380;0.326555;,
  -0.113082;-0.136047;0.984227;,
  -0.927246;0.277208;0.251736;,
  -0.943375;0.123970;0.307695;,
  -0.936158;0.173428;-0.305830;,
  -0.897684;0.141623;-0.417261;,
  -0.412285;0.058870;-0.909151;,
  -0.197770;-0.026308;-0.979895;,
  -0.022300;-0.091764;-0.995531;,
  0.131917;-0.034420;-0.990663;,
  0.649774;-0.054258;-0.758188;,
  0.816206;-0.120414;-0.565074;,
  0.965432;0.212429;-0.151047;,
  0.980844;0.191877;0.033579;,
  0.831314;0.327039;0.449402;,
  0.978722;0.153771;-0.135857;,
  0.444973;0.290211;0.847217;,
  0.761685;0.415875;0.496874;,
  -0.053597;0.381658;0.922748;,
  0.377342;0.430833;0.819754;,
  -0.890605;0.348334;0.292381;,
  0.180273;0.516677;0.836987;,
  -0.962811;0.265617;0.049417;,
  -0.930248;0.357998;-0.080479;,
  -0.900120;0.261209;-0.348647;,
  -0.602271;0.423919;-0.676434;,
  -0.338811;0.541813;-0.769185;,
  -0.201099;0.548522;-0.811593;,
  -0.021226;0.554843;-0.831685;,
  0.152732;0.603205;-0.782826;,
  0.543584;0.079203;-0.835609;,
  0.955584;0.249732;-0.156502;,
  0.842931;0.536329;-0.042638;,
  0.874328;0.142670;0.463891;,
  0.871838;0.094854;0.480523;,
  0.753373;0.647988;-0.111985;,
  0.269704;0.921559;0.279266;,
  0.240723;0.932893;0.267887;,
  0.009871;0.994222;-0.106891;,
  -0.081952;0.853353;0.514852;,
  0.047785;0.942138;0.331802;,
  -0.225321;0.911492;0.344112;,
  0.144349;0.874740;0.462594;,
  -0.693654;0.444109;-0.567108;,
  0.005904;0.866328;0.499440;,
  -0.245380;0.850012;-0.466121;,
  -0.141021;0.902170;-0.407679;,
  -0.158874;0.845396;-0.509966;,
  -0.084505;0.852990;-0.515041;,
  0.040565;0.870972;-0.489655;,
  0.103785;0.898266;-0.427020;,
  0.034465;0.871671;-0.488879;,
  0.001246;0.949617;-0.313412;,
  0.397810;0.917355;-0.014381;,
  0.171003;0.972885;-0.155735;,
  0.184222;0.978628;0.091373;,
  0.190144;0.980540;0.048863;,
  0.407650;-0.193562;0.892387;,
  0.752374;0.052895;0.656609;,
  -0.072893;-0.221314;0.972475;,
  0.282062;0.040316;0.958549;,
  -0.213823;-0.972942;0.087545;,
  -0.123734;0.039394;0.991533;,
  -0.160990;-0.982301;-0.095746;,
  -0.564808;0.049776;0.823719;,
  -0.348761;-0.410571;-0.842495;,
  -0.980639;0.065691;0.184479;,
  -0.249945;-0.284896;-0.925398;,
  -0.104984;-0.234213;-0.966500;,
  0.064181;-0.232642;-0.970442;,
  0.565307;-0.450028;-0.691305;,
  0.138452;-0.988816;-0.055433;,
  0.124138;0.044781;-0.991254;,
  0.158962;-0.982661;0.095441;,
  0.565051;0.053069;-0.823348;,
  0.346530;-0.415409;0.841042;,
  0.980194;0.066336;-0.186598;,
  -0.413661;-0.439868;0.797120;,
  -0.496418;-0.275393;0.823242;,
  -0.443276;-0.877820;0.181489;,
  -0.425321;-0.868975;-0.252952;,
  -0.399613;-0.280792;-0.872620;,
  -0.313299;-0.474875;-0.822397;,
  0.421706;-0.870665;0.253194;,
  -0.032939;-0.394500;0.918305;,
  -0.086938;-0.219702;0.971685;,
  -0.435719;0.559364;-0.705167;,
  -0.355449;0.701321;-0.617904;,
  -0.544481;-0.190352;0.816888;,
  -0.882486;-0.432413;0.185033;,
  -0.221894;0.208254;0.952572;,
  -0.222722;-0.491754;-0.841768;,
  -0.130922;-0.079534;0.988197;,
  -0.487628;-0.185360;0.853147;,
  -0.959308;-0.085538;0.269095;,
  -0.924424;0.223586;-0.308950;,
  -0.750666;-0.347247;0.562068;,
  -0.486739;0.214450;-0.846815;,
  -0.806527;-0.591070;-0.012240;,
  -0.318551;-0.177552;-0.931129;,
  0.969873;0.089351;0.226635;,
  0.751018;-0.345765;-0.562510;,
  -0.070002;0.008757;0.997509;,
  -0.436539;0.024706;0.899346;,
  -0.922312;0.380263;-0.068846;,
  -0.573520;0.473845;-0.668241;,
  -0.402476;-0.030414;-0.914925;,
  0.846819;0.079346;-0.525929;,
  0.947163;0.318064;-0.041440;,
  0.462360;0.514410;0.722223;,
  0.991278;0.078069;-0.106174;,
  0.037615;0.108739;0.993358;,
  -0.462790;0.261072;0.847152;,
  -0.948965;0.237550;-0.207450;,
  0.033198;0.100663;0.994367;,
  -0.496593;0.377357;0.781663;,
  -0.869962;0.432119;0.237571;,
  0.050348;0.948833;0.311739;,
  -0.088972;0.968773;-0.231437;,
  0.017413;0.894449;-0.446832;,
  -0.090231;0.874445;-0.476660;,
  0.765394;0.499796;0.405433;,
  0.286968;0.910133;-0.298843;,
  0.578928;-0.096642;0.809631;,
  0.380482;0.924142;-0.034567;,
  -0.023590;0.123204;0.992101;,
  0.000000;-1.000000;0.000000;,
  0.000117;-1.000000;-0.000759;,
  -0.000071;-0.999998;-0.001877;,
  -0.000690;-1.000000;-0.000395;,
  -0.003365;-0.999994;0.000699;,
  0.000204;-1.000000;-0.000308;,
  0.000528;-0.999999;0.001095;,
  -0.001375;-0.999985;0.005312;,
  -0.000394;-0.999993;0.003832;;
  158;
  4;121,0,1,122;,
  4;141,142,2,123;,
  4;123,2,3,124;,
  4;143,4,4,125;,
  4;126,5,5,126;,
  4;144,6,6,127;,
  4;128,7,7,128;,
  4;129,8,8,129;,
  4;130,9,9,130;,
  4;145,146,10,131;,
  4;131,10,11,132;,
  4;132,11,12,133;,
  4;133,12,13,134;,
  4;134,13,14,135;,
  4;136,136,15,136;,
  4;147,16,16,137;,
  4;138,17,17,138;,
  4;139,18,18,139;,
  4;140,19,19,140;,
  4;148,149,0,121;,
  3;100,102,101;,
  3;101,102,103;,
  3;103,102,104;,
  3;104,102,105;,
  3;105,102,106;,
  3;107,150,107;,
  3;108,102,108;,
  3;151,102,109;,
  3;109,102,110;,
  3;110,102,111;,
  3;111,102,112;,
  3;112,102,113;,
  3;113,102,114;,
  3;114,102,115;,
  3;115,102,116;,
  3;116,102,117;,
  3;117,102,118;,
  3;118,102,119;,
  3;119,102,120;,
  3;120,102,100;,
  4;0,20,21,1;,
  4;142,152,22,2;,
  4;2,22,23,3;,
  4;4,153,24,4;,
  4;5,154,25,5;,
  4;6,26,26,6;,
  4;7,27,27,7;,
  4;8,28,28,8;,
  4;9,29,29,9;,
  4;146,155,30,10;,
  4;10,30,31,11;,
  4;11,31,32,12;,
  4;12,32,33,13;,
  4;13,33,34,14;,
  4;14,34,35,15;,
  4;16,36,36,16;,
  4;17,37,37,17;,
  4;18,38,38,18;,
  4;19,39,39,19;,
  4;149,156,20,0;,
  4;20,40,41,21;,
  4;152,157,42,22;,
  4;22,42,43,23;,
  4;153,158,44,24;,
  4;24,44,45,25;,
  4;26,159,46,26;,
  4;27,160,47,27;,
  4;28,161,48,28;,
  4;29,162,49,29;,
  4;155,163,50,30;,
  4;30,50,51,31;,
  4;31,51,52,32;,
  4;32,52,53,33;,
  4;33,53,54,34;,
  4;34,54,55,35;,
  4;36,164,56,36;,
  4;37,165,57,37;,
  4;38,58,58,38;,
  4;39,59,59,39;,
  4;156,166,40,20;,
  4;40,60,61,41;,
  4;157,167,62,42;,
  4;42,62,63,43;,
  4;158,64,64,44;,
  4;44,65,65,45;,
  4;159,168,66,46;,
  4;46,66,67,47;,
  4;161,169,68,48;,
  4;48,68,69,49;,
  4;163,170,70,50;,
  4;50,70,71,51;,
  4;51,71,72,52;,
  4;52,72,73,53;,
  4;53,171,74,54;,
  4;54,74,75,55;,
  4;164,172,76,56;,
  4;56,76,77,57;,
  4;58,173,78,58;,
  4;59,174,79,59;,
  4;166,175,60,40;,
  4;60,80,81,61;,
  4;167,176,82,62;,
  4;62,82,83,63;,
  4;64,84,84,64;,
  4;65,85,85,65;,
  4;168,177,86,66;,
  4;66,86,87,67;,
  4;67,87,88,68;,
  4;68,88,89,69;,
  4;69,89,90,70;,
  4;70,90,91,71;,
  4;71,91,92,72;,
  4;72,92,93,73;,
  4;73,93,94,74;,
  4;74,94,95,75;,
  4;75,95,96,76;,
  4;76,96,97,77;,
  4;77,97,98,78;,
  4;78,98,99,79;,
  4;175,178,80,60;,
  4;80,100,101,81;,
  4;176,179,103,82;,
  4;82,103,104,83;,
  4;84,180,105,84;,
  4;85,105,106,85;,
  4;177,107,107,86;,
  4;181,108,108,181;,
  4;87,151,109,88;,
  4;182,109,110,182;,
  4;89,110,111,90;,
  4;90,111,112,91;,
  4;91,112,113,92;,
  4;92,113,114,93;,
  4;93,114,115,183;,
  4;183,115,116,184;,
  4;95,185,117,96;,
  4;96,117,118,186;,
  4;97,187,187,98;,
  4;188,119,120,99;,
  4;178,189,189,80;,
  3;190,190,191;,
  3;192,191,193;,
  3;194,193,137;,
  3;147,137,135;,
  3;190,195,127;,
  3;144,127,125;,
  3;143,125,190;,
  3;190,190,195;,
  3;190,196,195;,
  3;197,135,198;,
  3;198,135,196;,
  3;196,135,195;,
  3;135,137,195;,
  3;137,193,195;,
  3;193,191,195;,
  3;191,190,195;,
  3;195,190,127;,
  3;127,190,125;;
 }
 MeshTextureCoords {
  163;
  0.375000;0.405540;,
  0.375000;0.311560;,
  0.387500;0.311560;,
  0.387500;0.405540;,
  0.400000;0.311560;,
  0.400000;0.405540;,
  0.412500;0.311560;,
  0.412500;0.405540;,
  0.425000;0.311560;,
  0.425000;0.405540;,
  0.437500;0.311560;,
  0.437500;0.405540;,
  0.450000;0.311560;,
  0.450000;0.405540;,
  0.462500;0.311560;,
  0.462500;0.405540;,
  0.475000;0.311560;,
  0.475000;0.405540;,
  0.487500;0.311560;,
  0.487500;0.405540;,
  0.500000;0.311560;,
  0.500000;0.405540;,
  0.512500;0.311560;,
  0.512500;0.405540;,
  0.525000;0.311560;,
  0.525000;0.405540;,
  0.537500;0.311560;,
  0.537500;0.405540;,
  0.550000;0.311560;,
  0.550000;0.405540;,
  0.562500;0.311560;,
  0.562500;0.405540;,
  0.575000;0.311560;,
  0.575000;0.405540;,
  0.587500;0.311560;,
  0.587500;0.405540;,
  0.600000;0.311560;,
  0.600000;0.405540;,
  0.612500;0.311560;,
  0.612500;0.405540;,
  0.625000;0.311560;,
  0.625000;0.405540;,
  0.648600;0.107970;,
  0.500000;0.162500;,
  0.626410;0.064410;,
  0.591840;0.029840;,
  0.548280;0.007650;,
  0.500000;0.000000;,
  0.451720;0.007650;,
  0.408160;0.029840;,
  0.373590;0.064410;,
  0.351400;0.107970;,
  0.343750;0.156250;,
  0.351400;0.204530;,
  0.373590;0.248090;,
  0.408160;0.282660;,
  0.451720;0.304850;,
  0.500000;0.312500;,
  0.548280;0.304850;,
  0.591840;0.282660;,
  0.626410;0.248090;,
  0.648600;0.204530;,
  0.656250;0.156250;,
  0.648600;0.107970;,
  0.648600;0.107970;,
  0.626410;0.064410;,
  0.626410;0.064410;,
  0.591840;0.029840;,
  0.591840;0.029840;,
  0.548280;0.007650;,
  0.548280;0.007650;,
  0.500000;0.000000;,
  0.500000;0.000000;,
  0.451720;0.007650;,
  0.451720;0.007650;,
  0.408160;0.029840;,
  0.408160;0.029840;,
  0.373590;0.064410;,
  0.373590;0.064410;,
  0.351400;0.107970;,
  0.351400;0.107970;,
  0.343750;0.156250;,
  0.343750;0.156250;,
  0.351400;0.204530;,
  0.351400;0.204530;,
  0.373590;0.248090;,
  0.373590;0.248090;,
  0.408160;0.282660;,
  0.408160;0.282660;,
  0.451720;0.304850;,
  0.451720;0.304850;,
  0.500000;0.312500;,
  0.500000;0.312500;,
  0.548280;0.304850;,
  0.548280;0.304850;,
  0.591840;0.282660;,
  0.591840;0.282660;,
  0.626410;0.248090;,
  0.626410;0.248090;,
  0.648600;0.204530;,
  0.648600;0.204530;,
  0.656250;0.156250;,
  0.656250;0.156250;,
  0.648600;0.107970;,
  0.626410;0.064410;,
  0.591840;0.029840;,
  0.548280;0.007650;,
  0.500000;0.000000;,
  0.451720;0.007650;,
  0.408160;0.029840;,
  0.373590;0.064410;,
  0.351400;0.107970;,
  0.343750;0.156250;,
  0.351400;0.204530;,
  0.373590;0.248090;,
  0.408160;0.282660;,
  0.451720;0.304850;,
  0.500000;0.312500;,
  0.548280;0.304850;,
  0.591840;0.282660;,
  0.626410;0.248090;,
  0.648600;0.204530;,
  0.656250;0.156250;,
  0.648600;0.107970;,
  0.626410;0.064410;,
  0.591840;0.029840;,
  0.548280;0.007650;,
  0.500000;0.000000;,
  0.451720;0.007650;,
  0.408160;0.029840;,
  0.373590;0.064410;,
  0.351400;0.107970;,
  0.343750;0.156250;,
  0.351400;0.204530;,
  0.373590;0.248090;,
  0.408160;0.282660;,
  0.451720;0.304850;,
  0.500000;0.312500;,
  0.548280;0.304850;,
  0.591840;0.282660;,
  0.626410;0.248090;,
  0.648600;0.204530;,
  0.656250;0.156250;,
  0.648600;0.107970;,
  0.626410;0.064410;,
  0.591840;0.029840;,
  0.548280;0.007650;,
  0.500000;0.000000;,
  0.451720;0.007650;,
  0.408160;0.029840;,
  0.373590;0.064410;,
  0.351400;0.107970;,
  0.343750;0.156250;,
  0.351400;0.204530;,
  0.373590;0.248090;,
  0.408160;0.282660;,
  0.451720;0.304850;,
  0.500000;0.312500;,
  0.548280;0.304850;,
  0.591840;0.282660;,
  0.626410;0.248090;,
  0.648600;0.204530;,
  0.656250;0.156250;;
 }
}
