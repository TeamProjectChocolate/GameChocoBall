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
 0.50000;-0.42848;-0.42848;,
 0.42848;-0.42848;-0.50000;,
 0.42848;0.42848;-0.50000;,
 0.50000;0.42848;-0.42848;,
 0.42848;-0.42848;0.50000;,
 0.50000;-0.42848;0.42848;,
 0.50000;0.42848;0.42848;,
 0.42848;0.42848;0.50000;,
 -0.50000;0.42848;-0.42848;,
 -0.42848;0.42848;-0.50000;,
 -0.42848;-0.42848;-0.50000;,
 -0.50000;-0.42848;-0.42848;,
 -0.50000;-0.42848;0.42848;,
 -0.42848;-0.42848;0.50000;,
 -0.42848;0.42848;0.50000;,
 -0.50000;0.42848;0.42848;,
 -0.42848;0.50000;0.42848;,
 0.42848;0.50000;0.42848;,
 0.42848;0.50000;-0.42848;,
 -0.42848;0.50000;-0.42848;,
 -0.42848;-0.50000;-0.42848;,
 0.42848;-0.50000;-0.42848;,
 0.42848;-0.50000;0.42848;,
 -0.42848;-0.50000;0.42848;,
 0.40967;0.40967;-0.42801;,
 -0.40967;0.40967;-0.42801;,
 0.40967;-0.40967;-0.42801;,
 -0.40967;-0.40967;-0.42801;,
 0.42801;0.40967;0.40967;,
 0.42801;0.40967;-0.40967;,
 0.42801;-0.40967;0.40967;,
 0.42801;-0.40967;-0.40967;,
 -0.40967;0.40967;0.42801;,
 0.40967;0.40967;0.42801;,
 -0.40967;-0.40967;0.42801;,
 0.40967;-0.40967;0.42801;,
 -0.42801;0.40967;-0.40967;,
 -0.42801;0.40967;0.40967;,
 -0.42801;-0.40967;-0.40967;,
 -0.42801;-0.40967;0.40967;,
 0.40967;0.42801;0.40967;,
 -0.40967;0.42801;0.40967;,
 0.40967;0.42801;-0.40967;,
 -0.40967;0.42801;-0.40967;,
 0.40967;-0.42801;-0.40967;,
 -0.40967;-0.42801;-0.40967;,
 0.40967;-0.42801;0.40967;,
 -0.40967;-0.42801;0.40967;,
 -0.34518;0.34518;-0.49250;,
 0.34518;0.34518;-0.49250;,
 0.34518;-0.34518;-0.49250;,
 -0.34518;-0.34518;-0.49250;,
 0.49250;0.34518;-0.34518;,
 0.49250;0.34518;0.34518;,
 0.49250;-0.34518;0.34518;,
 0.49250;-0.34518;-0.34518;,
 0.34518;0.34518;0.49250;,
 -0.34518;0.34518;0.49250;,
 -0.34518;-0.34518;0.49250;,
 0.34518;-0.34518;0.49250;,
 -0.49250;0.34518;0.34518;,
 -0.49250;0.34518;-0.34518;,
 -0.49250;-0.34518;-0.34518;,
 -0.49250;-0.34518;0.34518;,
 -0.34518;0.49250;0.34518;,
 0.34518;0.49250;0.34518;,
 0.34518;0.49250;-0.34518;,
 -0.34518;0.49250;-0.34518;,
 -0.34518;-0.49250;-0.34518;,
 0.34518;-0.49250;-0.34518;,
 0.34518;-0.49250;0.34518;,
 -0.34518;-0.49250;0.34518;;
 
 74;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,14,7,17;,
 4;17,6,3,18;,
 4;18,2,9,19;,
 4;19,8,15,16;,
 4;20,10,1,21;,
 4;21,0,5,22;,
 4;22,4,13,23;,
 4;23,12,11,20;,
 3;8,19,9;,
 3;18,3,2;,
 3;0,21,1;,
 3;20,11,10;,
 3;17,7,6;,
 3;4,22,5;,
 3;16,15,14;,
 3;12,23,13;,
 4;24,25,9,2;,
 4;26,24,2,1;,
 4;27,26,1,10;,
 4;25,27,10,9;,
 4;28,29,3,6;,
 4;30,28,6,5;,
 4;31,30,5,0;,
 4;29,31,0,3;,
 4;32,33,7,14;,
 4;34,32,14,13;,
 4;35,34,13,4;,
 4;33,35,4,7;,
 4;36,37,15,8;,
 4;38,36,8,11;,
 4;39,38,11,12;,
 4;37,39,12,15;,
 4;40,41,16,17;,
 4;42,40,17,18;,
 4;43,42,18,19;,
 4;41,43,19,16;,
 4;44,45,20,21;,
 4;46,44,21,22;,
 4;47,46,22,23;,
 4;45,47,23,20;,
 4;48,49,50,51;,
 4;25,24,49,48;,
 4;24,26,50,49;,
 4;26,27,51,50;,
 4;27,25,48,51;,
 4;52,53,54,55;,
 4;29,28,53,52;,
 4;28,30,54,53;,
 4;30,31,55,54;,
 4;31,29,52,55;,
 4;56,57,58,59;,
 4;33,32,57,56;,
 4;32,34,58,57;,
 4;34,35,59,58;,
 4;35,33,56,59;,
 4;60,61,62,63;,
 4;37,36,61,60;,
 4;36,38,62,61;,
 4;38,39,63,62;,
 4;39,37,60,63;,
 4;64,65,66,67;,
 4;41,40,65,64;,
 4;40,42,66,65;,
 4;42,43,67,66;,
 4;43,41,64,67;,
 4;68,69,70,71;,
 4;45,44,69,68;,
 4;44,46,70,69;,
 4;46,47,71,70;,
 4;47,45,68,71;;
 
 MeshMaterialList {
  1;
  74;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.488000;0.488000;0.488000;1.000000;;
   5.000000;
   0.112000;0.112000;0.112000;;
   0.488000;0.488000;0.488000;;
   TextureFilename {
    "image\\BR.png";
   }
  }
 }
}
