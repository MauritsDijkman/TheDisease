#include "Level.h"

Level::Level(int wallNum_){
	wallNum = wallNum_;
	walls = new Wall * [wallNum];
	for (int i = 0; i < wallNum; i++) {
		walls[i] = new Wall;
		walls[i]->setBoundingBoxWidth(1.0f);
		walls[i]->setBoundingBoxHeight(1.0f);
	}
}

Level::~Level(){
	for (int i = 0; i < wallNum; i++)
		delete walls[i];
	delete walls;
}

// Makes the level by placing all the walls
void Level::makeLevel(int sceneNum){
	switch (sceneNum){
	case 1:
		//Interior walls       x.x    y.y    z.z
#pragma region leftwall	
		//left wall
walls[0]->setPos(Vec3(-250.0f, 50.0f, 0.0f)); walls[1]->setPos(Vec3(-250.0f, 49.0f, 0.0f)); walls[2]->setPos(Vec3(-250.0f, 48.0f, 0.0f)); walls[3]->setPos(Vec3(-250.0f, 47.0f, 0.0f));
walls[4]->setPos(Vec3(-250.0f, 46.0f, 0.0f)); walls[5]->setPos(Vec3(-250.0f, 45.0f, 0.0f));walls[6]->setPos(Vec3(-250.0f, 44.0f, 0.0f)); walls[7]->setPos(Vec3(-250.0f, 43.0f, 0.0f));
walls[8]->setPos(Vec3(-250.0f, 42.0f, 0.0f)); walls[9]->setPos(Vec3(-250.0f, 41.0f, 0.0f));walls[10]->setPos(Vec3(-250.0f, 40.0f, 0.0f)); walls[11]->setPos(Vec3(-250.0f, 39.0f, 0.0f));
walls[12]->setPos(Vec3(-250.0f, 38.0f, 0.0f)); walls[13]->setPos(Vec3(-250.0f, 37.0f, 0.0f));walls[14]->setPos(Vec3(-250.0f, 36.0f, 0.0f)); walls[15]->setPos(Vec3(-250.0f, 35.0f, 0.0f));
walls[16]->setPos(Vec3(-250.0f, 34.0f, 0.0f)); walls[17]->setPos(Vec3(-250.0f, 33.0f, 0.0f));walls[18]->setPos(Vec3(-250.0f, 32.0f, 0.0f)); walls[19]->setPos(Vec3(-250.0f, 31.0f, 0.0f));
walls[20]->setPos(Vec3(-250.0f, 30.0f, 0.0f)); walls[21]->setPos(Vec3(-250.0f, 29.0f, 0.0f));walls[22]->setPos(Vec3(-250.0f, 28.0f, 0.0f)); walls[23]->setPos(Vec3(-250.0f, 27.0f, 0.0f));
walls[24]->setPos(Vec3(-250.0f, 26.0f, 0.0f)); walls[25]->setPos(Vec3(-250.0f, 25.0f, 0.0f)); walls[26]->setPos(Vec3(-250.0f, 24.0f, 0.0f)); walls[27]->setPos(Vec3(-250.0f, 23.0f, 0.0f));
walls[28]->setPos(Vec3(-250.0f, 22.0f, 0.0f)); walls[29]->setPos(Vec3(-250.0f, 21.0f, 0.0f)); walls[30]->setPos(Vec3(-250.0f, 20.0f, 0.0f)); walls[31]->setPos(Vec3(-250.0f, 19.0f, 0.0f));
walls[32]->setPos(Vec3(-250.0f, 18.0f, 0.0f)); walls[33]->setPos(Vec3(-250.0f, 17.0f, 0.0f)); walls[34]->setPos(Vec3(-250.0f, 16.0f, 0.0f)); walls[35]->setPos(Vec3(-250.0f, 15.0f, 0.0f));
walls[36]->setPos(Vec3(-250.0f, 14.0f, 0.0f)); walls[37]->setPos(Vec3(-250.0f, 13.0f, 0.0f)); walls[38]->setPos(Vec3(-250.0f, 12.0f, 0.0f)); walls[39]->setPos(Vec3(-250.0f, 11.0f, 0.0f));
walls[40]->setPos(Vec3(-250.0f, 10.0f, 0.0f)); walls[41]->setPos(Vec3(-250.0f, 9.0f, 0.0f)); walls[42]->setPos(Vec3(-250.0f, 8.0f, 0.0f)); walls[43]->setPos(Vec3(-250.0f, 7.0f, 0.0f));
walls[44]->setPos(Vec3(-250.0f, 6.0f, 0.0f)); walls[45]->setPos(Vec3(-250.0f, 5.0f, 0.0f)); walls[46]->setPos(Vec3(-250.0f, 4.0f, 0.0f)); walls[47]->setPos(Vec3(-250.0f, 3.0f, 0.0f));
walls[48]->setPos(Vec3(-250.0f, 2.0f, 0.0f)); walls[49]->setPos(Vec3(-250.0f, 1.0f, 0.0f)); walls[50]->setPos(Vec3(-250.0f, 0.0f, 0.0f)); walls[51]->setPos(Vec3(-250.0f, -1.0f, 0.0f));
walls[52]->setPos(Vec3(-250.0f, -2.0f, 0.0f)); walls[53]->setPos(Vec3(-250.0f, -3.0f, 0.0f)); walls[54]->setPos(Vec3(-250.0f, -4.0f, 0.0f)); walls[55]->setPos(Vec3(-250.0f, -5.0f, 0.0f));
walls[56]->setPos(Vec3(-250.0f, -6.0f, 0.0f)); walls[57]->setPos(Vec3(-250.0f, -7.0f, 0.0f)); walls[58]->setPos(Vec3(-250.0f, -8.0f, 0.0f)); walls[59]->setPos(Vec3(-250.0f, -9.0f, 0.0f));
walls[60]->setPos(Vec3(-250.0f, -10.0f, 0.0f)); walls[61]->setPos(Vec3(-250.0f, -11.0f, 0.0f)); walls[62]->setPos(Vec3(-250.0f, -12.0f, 0.0f)); walls[63]->setPos(Vec3(-250.0f, -13.0f, 0.0f));
walls[64]->setPos(Vec3(-250.0f, -14.0f, 0.0f)); walls[65]->setPos(Vec3(-250.0f, -15.0f, 0.0f)); walls[66]->setPos(Vec3(-250.0f, -16.0f, 0.0f)); walls[67]->setPos(Vec3(-250.0f, -17.0f, 0.0f));
walls[68]->setPos(Vec3(-250.0f, -18.0f, 0.0f)); walls[69]->setPos(Vec3(-250.0f, -19.0f, 0.0f)); walls[70]->setPos(Vec3(-250.0f, -20.0f, 0.0f)); walls[71]->setPos(Vec3(-250.0f, -21.0f, 0.0f));
walls[72]->setPos(Vec3(-250.0f, -22.0f, 0.0f)); walls[73]->setPos(Vec3(-250.0f, -23.0f, 0.0f)); walls[74]->setPos(Vec3(-250.0f, -24.0f, 0.0f)); walls[75]->setPos(Vec3(-250.0f, -25.0f, 0.0f));
walls[76]->setPos(Vec3(-250.0f, -26.0f, 0.0f)); walls[77]->setPos(Vec3(-250.0f, -27.0f, 0.0f)); walls[78]->setPos(Vec3(-250.0f, -28.0f, 0.0f)); walls[79]->setPos(Vec3(-250.0f, -29.0f, 0.0f));
walls[80]->setPos(Vec3(-250.0f, -30.0f, 0.0f)); walls[81]->setPos(Vec3(-250.0f, -31.0f, 0.0f)); walls[82]->setPos(Vec3(-250.0f, -32.0f, 0.0f)); walls[83]->setPos(Vec3(-250.0f, -33.0f, 0.0f));
walls[84]->setPos(Vec3(-250.0f, -34.0f, 0.0f)); walls[85]->setPos(Vec3(-250.0f, -35.0f, 0.0f)); walls[86]->setPos(Vec3(-250.0f, -36.0f, 0.0f)); walls[87]->setPos(Vec3(-250.0f, -37.0f, 0.0f));
walls[88]->setPos(Vec3(-250.0f, -38.0f, 0.0f)); walls[89]->setPos(Vec3(-250.0f, -39.0f, 0.0f)); walls[90]->setPos(Vec3(-250.0f, -40.0f, 0.0f)); walls[91]->setPos(Vec3(-250.0f, -41.0f, 0.0f));
walls[92]->setPos(Vec3(-250.0f, -42.0f, 0.0f)); walls[93]->setPos(Vec3(-250.0f, -43.0f, 0.0f)); walls[94]->setPos(Vec3(-250.0f, -44.0f, 0.0f)); walls[95]->setPos(Vec3(-250.0f, -45.0f, 0.0f));
walls[96]->setPos(Vec3(-250.0f, -46.0f, 0.0f)); walls[97]->setPos(Vec3(-250.0f, -47.0f, 0.0f)); walls[98]->setPos(Vec3(-250.0f, -48.0f, 0.0f)); walls[99]->setPos(Vec3(-250.0f, -49.0f, 0.0f));
walls[100]->setPos(Vec3(-250.0f, -50.0f, 0.0f));
#pragma endregion

#pragma region rightwall
		//right wall
walls[101]->setPos(Vec3(250.0f, 50.0f, 0.0f)); walls[102]->setPos(Vec3(250.0f, 49.0f, 0.0f));walls[103]->setPos(Vec3(250.0f, 48.0f, 0.0f)); walls[104]->setPos(Vec3(250.0f, 47.0f, 0.0f));
walls[105]->setPos(Vec3(250.0f, 46.0f, 0.0f)); walls[106]->setPos(Vec3(250.0f, 45.0f, 0.0f));walls[107]->setPos(Vec3(250.0f, 44.0f, 0.0f)); walls[108]->setPos(Vec3(250.0f, 43.0f, 0.0f));
walls[109]->setPos(Vec3(250.0f, 42.0f, 0.0f)); walls[110]->setPos(Vec3(250.0f, 41.0f, 0.0f));walls[111]->setPos(Vec3(250.0f, 40.0f, 0.0f)); walls[112]->setPos(Vec3(250.0f, 39.0f, 0.0f));
walls[113]->setPos(Vec3(250.0f, 38.0f, 0.0f)); walls[114]->setPos(Vec3(250.0f, 37.0f, 0.0f));walls[115]->setPos(Vec3(250.0f, 36.0f, 0.0f)); walls[116]->setPos(Vec3(250.0f, 35.0f, 0.0f));
walls[117]->setPos(Vec3(250.0f, 34.0f, 0.0f)); walls[118]->setPos(Vec3(250.0f, 33.0f, 0.0f));walls[119]->setPos(Vec3(250.0f, 32.0f, 0.0f)); walls[120]->setPos(Vec3(250.0f, 31.0f, 0.0f));
walls[121]->setPos(Vec3(250.0f, 30.0f, 0.0f)); walls[122]->setPos(Vec3(250.0f, 29.0f, 0.0f));walls[123]->setPos(Vec3(250.0f, 28.0f, 0.0f)); walls[124]->setPos(Vec3(250.0f, 27.0f, 0.0f));
walls[125]->setPos(Vec3(250.0f, 26.0f, 0.0f)); walls[126]->setPos(Vec3(250.0f, 25.0f, 0.0f));walls[127]->setPos(Vec3(250.0f, 24.0f, 0.0f)); walls[128]->setPos(Vec3(250.0f, 23.0f, 0.0f));
walls[129]->setPos(Vec3(250.0f, 22.0f, 0.0f)); walls[130]->setPos(Vec3(250.0f, 21.0f, 0.0f));walls[131]->setPos(Vec3(250.0f, 20.0f, 0.0f)); walls[132]->setPos(Vec3(250.0f, 19.0f, 0.0f));
walls[133]->setPos(Vec3(250.0f, 18.0f, 0.0f)); walls[134]->setPos(Vec3(250.0f, 17.0f, 0.0f));walls[135]->setPos(Vec3(250.0f, 16.0f, 0.0f)); walls[136]->setPos(Vec3(250.0f, 15.0f, 0.0f));
walls[137]->setPos(Vec3(250.0f, 14.0f, 0.0f)); walls[138]->setPos(Vec3(250.0f, 13.0f, 0.0f));walls[139]->setPos(Vec3(250.0f, 12.0f, 0.0f)); walls[140]->setPos(Vec3(250.0f, 11.0f, 0.0f));
walls[141]->setPos(Vec3(250.0f, 10.0f, 0.0f)); walls[142]->setPos(Vec3(250.0f, 9.0f, 0.0f));walls[143]->setPos(Vec3(250.0f, 8.0f, 0.0f)); walls[144]->setPos(Vec3(250.0f, 7.0f, 0.0f));
walls[145]->setPos(Vec3(250.0f, 6.0f, 0.0f)); walls[146]->setPos(Vec3(250.0f, 5.0f, 0.0f)); walls[147]->setPos(Vec3(250.0f, 4.0f, 0.0f)); walls[148]->setPos(Vec3(250.0f, 3.0f, 0.0f));
walls[149]->setPos(Vec3(250.0f, 2.0f, 0.0f)); walls[150]->setPos(Vec3(250.0f, 1.0f, 0.0f));walls[151]->setPos(Vec3(250.0f, 0.0f, 0.0f)); walls[152]->setPos(Vec3(250.0f, -1.0f, 0.0f));
walls[153]->setPos(Vec3(250.0f, -2.0f, 0.0f)); walls[154]->setPos(Vec3(250.0f, -3.0f, 0.0f));walls[155]->setPos(Vec3(250.0f, -4.0f, 0.0f)); walls[156]->setPos(Vec3(250.0f, -5.0f, 0.0f));
walls[157]->setPos(Vec3(250.0f, -6.0f, 0.0f)); walls[158]->setPos(Vec3(250.0f, -7.0f, 0.0f));walls[159]->setPos(Vec3(250.0f, -8.0f, 0.0f)); walls[160]->setPos(Vec3(250.0f, -9.0f, 0.0f));
walls[161]->setPos(Vec3(250.0f, -10.0f, 0.0f)); walls[162]->setPos(Vec3(250.0f, -11.0f, 0.0f));walls[163]->setPos(Vec3(250.0f, -12.0f, 0.0f)); walls[164]->setPos(Vec3(250.0f, -13.0f, 0.0f));
walls[165]->setPos(Vec3(250.0f, -14.0f, 0.0f)); walls[167]->setPos(Vec3(250.0f, -15.0f, 0.0f));walls[168]->setPos(Vec3(250.0f, -16.0f, 0.0f)); walls[169]->setPos(Vec3(250.0f, -17.0f, 0.0f));
walls[170]->setPos(Vec3(250.0f, -18.0f, 0.0f)); walls[171]->setPos(Vec3(250.0f, -19.0f, 0.0f));walls[172]->setPos(Vec3(250.0f, -20.0f, 0.0f)); walls[173]->setPos(Vec3(250.0f, -21.0f, 0.0f));
walls[174]->setPos(Vec3(250.0f, -22.0f, 0.0f)); walls[175]->setPos(Vec3(250.0f, -23.0f, 0.0f));walls[176]->setPos(Vec3(250.0f, -24.0f, 0.0f)); walls[177]->setPos(Vec3(250.0f, -25.0f, 0.0f));
walls[178]->setPos(Vec3(250.0f, -26.0f, 0.0f)); walls[179]->setPos(Vec3(250.0f, -27.0f, 0.0f));walls[180]->setPos(Vec3(250.0f, -28.0f, 0.0f)); walls[181]->setPos(Vec3(250.0f, -29.0f, 0.0f));
walls[182]->setPos(Vec3(250.0f, -30.0f, 0.0f)); walls[183]->setPos(Vec3(250.0f, -31.0f, 0.0f));walls[184]->setPos(Vec3(250.0f, -32.0f, 0.0f)); walls[185]->setPos(Vec3(250.0f, -33.0f, 0.0f));
walls[186]->setPos(Vec3(250.0f, -34.0f, 0.0f)); walls[187]->setPos(Vec3(250.0f, -35.0f, 0.0f)); walls[188]->setPos(Vec3(250.0f, -36.0f, 0.0f)); walls[189]->setPos(Vec3(250.0f, -37.0f, 0.0f));
walls[190]->setPos(Vec3(250.0f, -38.0f, 0.0f)); walls[191]->setPos(Vec3(250.0f, -39.0f, 0.0f)); walls[192]->setPos(Vec3(250.0f, -40.0f, 0.0f)); walls[193]->setPos(Vec3(250.0f, -41.0f, 0.0f));
walls[194]->setPos(Vec3(250.0f, -42.0f, 0.0f)); walls[195]->setPos(Vec3(250.0f, -43.0f, 0.0f)); walls[196]->setPos(Vec3(250.0f, -44.0f, 0.0f)); walls[197]->setPos(Vec3(250.0f, -45.0f, 0.0f));
walls[198]->setPos(Vec3(250.0f, -46.0f, 0.0f));	walls[199]->setPos(Vec3(250.0f, -47.0f, 0.0f)); walls[200]->setPos(Vec3(250.0f, -48.0f, 0.0f));	walls[201]->setPos(Vec3(250.0f, -49.0f, 0.0f));
walls[202]->setPos(Vec3(250.0f, -50.0f, 0.0f));
#pragma endregion

#pragma region downwall
		// down wall
walls[203]->setPos(Vec3(-249.0f, -50.0f, 0.0f)); walls[204]->setPos(Vec3(-248.0f, -50.0f, 0.0f));walls[205]->setPos(Vec3(-247.0f, -50.0f, 0.0f)); walls[206]->setPos(Vec3(-246.0f, -50.0f, 0.0f));
walls[207]->setPos(Vec3(-245.0f, -50.0f, 0.0f)); walls[208]->setPos(Vec3(-244.0f, -50.0f, 0.0f));walls[209]->setPos(Vec3(-243.0f, -50.0f, 0.0f)); walls[210]->setPos(Vec3(-242.0f, -50.0f, 0.0f));
walls[211]->setPos(Vec3(-241.0f, -50.0f, 0.0f)); walls[212]->setPos(Vec3(-240.0f, -50.0f, 0.0f));walls[213]->setPos(Vec3(-239.0f, -50.0f, 0.0f)); walls[214]->setPos(Vec3(-238.0f, -50.0f, 0.0f));
walls[215]->setPos(Vec3(-237.0f, -50.0f, 0.0f)); walls[216]->setPos(Vec3(-236.0f, -50.0f, 0.0f));walls[217]->setPos(Vec3(-235.0f, -50.0f, 0.0f)); walls[218]->setPos(Vec3(-234.0f, -50.0f, 0.0f));
walls[219]->setPos(Vec3(-233.0f, -50.0f, 0.0f)); walls[220]->setPos(Vec3(-232.0f, -50.0f, 0.0f));walls[221]->setPos(Vec3(-231.0f, -50.0f, 0.0f)); walls[222]->setPos(Vec3(-230.0f, -50.0f, 0.0f));
walls[223]->setPos(Vec3(-229.0f, -50.0f, 0.0f)); walls[224]->setPos(Vec3(-228.0f, -50.0f, 0.0f));walls[225]->setPos(Vec3(-227.0f, -50.0f, 0.0f)); walls[226]->setPos(Vec3(-226.0f, -50.0f, 0.0f));
walls[227]->setPos(Vec3(-225.0f, -50.0f, 0.0f)); walls[228]->setPos(Vec3(-224.0f, -50.0f, 0.0f));walls[229]->setPos(Vec3(-223.0f, -50.0f, 0.0f)); walls[230]->setPos(Vec3(-222.0f, -50.0f, 0.0f));
walls[231]->setPos(Vec3(-221.0f, -50.0f, 0.0f)); walls[232]->setPos(Vec3(-220.0f, -50.0f, 0.0f));walls[233]->setPos(Vec3(-219.0f, -50.0f, 0.0f)); walls[234]->setPos(Vec3(-218.0f, -50.0f, 0.0f));
walls[235]->setPos(Vec3(-217.0f, -50.0f, 0.0f)); walls[236]->setPos(Vec3(-216.0f, -50.0f, 0.0f));walls[237]->setPos(Vec3(-215.0f, -50.0f, 0.0f)); walls[238]->setPos(Vec3(-214.0f, -50.0f, 0.0f));
walls[239]->setPos(Vec3(-213.0f, -50.0f, 0.0f)); walls[240]->setPos(Vec3(-212.0f, -50.0f, 0.0f));walls[241]->setPos(Vec3(-211.0f, -50.0f, 0.0f)); walls[242]->setPos(Vec3(-210.0f, -50.0f, 0.0f));
walls[243]->setPos(Vec3(-209.0f, -50.0f, 0.0f)); walls[244]->setPos(Vec3(-208.0f, -50.0f, 0.0f));walls[245]->setPos(Vec3(-207.0f, -50.0f, 0.0f)); walls[246]->setPos(Vec3(-206.0f, -50.0f, 0.0f));
walls[247]->setPos(Vec3(-205.0f, -50.0f, 0.0f)); walls[248]->setPos(Vec3(-204.0f, -50.0f, 0.0f));walls[249]->setPos(Vec3(-203.0f, -50.0f, 0.0f)); walls[250]->setPos(Vec3(-202.0f, -50.0f, 0.0f));
walls[251]->setPos(Vec3(-201.0f, -50.0f, 0.0f)); walls[252]->setPos(Vec3(-200.0f, -50.0f, 0.0f));walls[253]->setPos(Vec3(-199.0f, -50.0f, 0.0f)); walls[254]->setPos(Vec3(-198.0f, -50.0f, 0.0f));
walls[255]->setPos(Vec3(-197.0f, -50.0f, 0.0f)); walls[256]->setPos(Vec3(-196.0f, -50.0f, 0.0f));walls[257]->setPos(Vec3(-195.0f, -50.0f, 0.0f)); walls[258]->setPos(Vec3(-194.0f, -50.0f, 0.0f));
walls[259]->setPos(Vec3(-193.0f, -50.0f, 0.0f)); walls[260]->setPos(Vec3(-192.0f, -50.0f, 0.0f));walls[261]->setPos(Vec3(-191.0f, -50.0f, 0.0f)); walls[262]->setPos(Vec3(-190.0f, -50.0f, 0.0f));
walls[263]->setPos(Vec3(-189.0f, -50.0f, 0.0f)); walls[264]->setPos(Vec3(-188.0f, -50.0f, 0.0f));walls[265]->setPos(Vec3(-187.0f, -50.0f, 0.0f)); walls[266]->setPos(Vec3(-186.0f, -50.0f, 0.0f));
walls[267]->setPos(Vec3(-185.0f, -50.0f, 0.0f)); walls[268]->setPos(Vec3(-184.0f, -50.0f, 0.0f));walls[269]->setPos(Vec3(-183.0f, -50.0f, 0.0f)); walls[270]->setPos(Vec3(-182.0f, -50.0f, 0.0f));
walls[271]->setPos(Vec3(-181.0f, -50.0f, 0.0f)); walls[272]->setPos(Vec3(-180.0f, -50.0f, 0.0f));walls[273]->setPos(Vec3(-179.0f, -50.0f, 0.0f)); walls[274]->setPos(Vec3(-178.0f, -50.0f, 0.0f));
walls[275]->setPos(Vec3(-177.0f, -50.0f, 0.0f)); walls[276]->setPos(Vec3(-176.0f, -50.0f, 0.0f));walls[277]->setPos(Vec3(-175.0f, -50.0f, 0.0f)); walls[278]->setPos(Vec3(-174.0f, -50.0f, 0.0f));
walls[279]->setPos(Vec3(-173.0f, -50.0f, 0.0f)); walls[280]->setPos(Vec3(-172.0f, -50.0f, 0.0f));walls[281]->setPos(Vec3(-171.0f, -50.0f, 0.0f)); walls[282]->setPos(Vec3(-170.0f, -50.0f, 0.0f));
walls[283]->setPos(Vec3(-169.0f, -50.0f, 0.0f)); walls[284]->setPos(Vec3(-168.0f, -50.0f, 0.0f));walls[285]->setPos(Vec3(-167.0f, -50.0f, 0.0f)); walls[286]->setPos(Vec3(-166.0f, -50.0f, 0.0f));
walls[287]->setPos(Vec3(-165.0f, -50.0f, 0.0f)); walls[288]->setPos(Vec3(-164.0f, -50.0f, 0.0f));walls[289]->setPos(Vec3(-163.0f, -50.0f, 0.0f)); walls[290]->setPos(Vec3(-162.0f, -50.0f, 0.0f));	
walls[291]->setPos(Vec3(-161.0f, -50.0f, 0.0f)); walls[292]->setPos(Vec3(-160.0f, -50.0f, 0.0f));walls[293]->setPos(Vec3(-159.0f, -50.0f, 0.0f)); walls[294]->setPos(Vec3(-158.0f, -50.0f, 0.0f));
walls[295]->setPos(Vec3(-157.0f, -50.0f, 0.0f)); walls[296]->setPos(Vec3(-156.0f, -50.0f, 0.0f));walls[297]->setPos(Vec3(-155.0f, -50.0f, 0.0f)); walls[298]->setPos(Vec3(-154.0f, -50.0f, 0.0f));
walls[299]->setPos(Vec3(-153.0f, -50.0f, 0.0f)); walls[300]->setPos(Vec3(-152.0f, -50.0f, 0.0f));walls[301]->setPos(Vec3(-151.0f, -50.0f, 0.0f)); walls[302]->setPos(Vec3(-150.0f, -50.0f, 0.0f));
walls[303]->setPos(Vec3(-149.0f, -50.0f, 0.0f)); walls[304]->setPos(Vec3(-148.0f, -50.0f, 0.0f));walls[305]->setPos(Vec3(-147.0f, -50.0f, 0.0f)); walls[306]->setPos(Vec3(-146.0f, -50.0f, 0.0f));
walls[307]->setPos(Vec3(-145.0f, -50.0f, 0.0f)); walls[308]->setPos(Vec3(-144.0f, -50.0f, 0.0f));walls[309]->setPos(Vec3(-143.0f, -50.0f, 0.0f)); walls[310]->setPos(Vec3(-142.0f, -50.0f, 0.0f));
walls[311]->setPos(Vec3(-141.0f, -50.0f, 0.0f)); walls[312]->setPos(Vec3(-140.0f, -50.0f, 0.0f));walls[313]->setPos(Vec3(-139.0f, -50.0f, 0.0f)); walls[314]->setPos(Vec3(-138.0f, -50.0f, 0.0f));
walls[315]->setPos(Vec3(-137.0f, -50.0f, 0.0f)); walls[316]->setPos(Vec3(-136.0f, -50.0f, 0.0f));walls[317]->setPos(Vec3(-135.0f, -50.0f, 0.0f)); walls[318]->setPos(Vec3(-134.0f, -50.0f, 0.0f));
walls[319]->setPos(Vec3(-133.0f, -50.0f, 0.0f)); walls[320]->setPos(Vec3(-132.0f, -50.0f, 0.0f));walls[321]->setPos(Vec3(-131.0f, -50.0f, 0.0f)); walls[322]->setPos(Vec3(-130.0f, -50.0f, 0.0f));
walls[323]->setPos(Vec3(-129.0f, -50.0f, 0.0f)); walls[324]->setPos(Vec3(-128.0f, -50.0f, 0.0f));walls[325]->setPos(Vec3(-127.0f, -50.0f, 0.0f)); walls[326]->setPos(Vec3(-126.0f, -50.0f, 0.0f));
walls[327]->setPos(Vec3(-125.0f, -50.0f, 0.0f)); walls[328]->setPos(Vec3(-124.0f, -50.0f, 0.0f));walls[329]->setPos(Vec3(-123.0f, -50.0f, 0.0f)); walls[330]->setPos(Vec3(-122.0f, -50.0f, 0.0f));
walls[331]->setPos(Vec3(-121.0f, -50.0f, 0.0f)); walls[332]->setPos(Vec3(-120.0f, -50.0f, 0.0f));walls[333]->setPos(Vec3(-119.0f, -50.0f, 0.0f)); walls[334]->setPos(Vec3(-118.0f, -50.0f, 0.0f));
walls[335]->setPos(Vec3(-117.0f, -50.0f, 0.0f)); walls[336]->setPos(Vec3(-116.0f, -50.0f, 0.0f));walls[337]->setPos(Vec3(-115.0f, -50.0f, 0.0f)); walls[338]->setPos(Vec3(-114.0f, -50.0f, 0.0f));
walls[339]->setPos(Vec3(-113.0f, -50.0f, 0.0f)); walls[340]->setPos(Vec3(-112.0f, -50.0f, 0.0f));walls[341]->setPos(Vec3(-111.0f, -50.0f, 0.0f)); walls[342]->setPos(Vec3(-110.0f, -50.0f, 0.0f));
walls[343]->setPos(Vec3(-109.0f, -50.0f, 0.0f)); walls[344]->setPos(Vec3(-108.0f, -50.0f, 0.0f));walls[345]->setPos(Vec3(-107.0f, -50.0f, 0.0f)); walls[346]->setPos(Vec3(-106.0f, -50.0f, 0.0f));
walls[347]->setPos(Vec3(-105.0f, -50.0f, 0.0f)); walls[348]->setPos(Vec3(-104.0f, -50.0f, 0.0f));walls[349]->setPos(Vec3(-103.0f, -50.0f, 0.0f)); walls[350]->setPos(Vec3(-102.0f, -50.0f, 0.0f));
walls[351]->setPos(Vec3(-101.0f, -50.0f, 0.0f)); walls[352]->setPos(Vec3(-100.0f, -50.0f, 0.0f));walls[353]->setPos(Vec3(-99.0f, -50.0f, 0.0f)); walls[354]->setPos(Vec3(-98.0f, -50.0f, 0.0f));
walls[355]->setPos(Vec3(-97.0f, -50.0f, 0.0f)); walls[356]->setPos(Vec3(-96.0f, -50.0f, 0.0f));walls[357]->setPos(Vec3(-95.0f, -50.0f, 0.0f)); walls[358]->setPos(Vec3(-94.0f, -50.0f, 0.0f));
walls[359]->setPos(Vec3(-93.0f, -50.0f, 0.0f)); walls[360]->setPos(Vec3(-92.0f, -50.0f, 0.0f));walls[361]->setPos(Vec3(-91.0f, -50.0f, 0.0f)); walls[362]->setPos(Vec3(-90.0f, -50.0f, 0.0f));
walls[363]->setPos(Vec3(-89.0f, -50.0f, 0.0f)); walls[364]->setPos(Vec3(-88.0f, -50.0f, 0.0f));walls[365]->setPos(Vec3(-87.0f, -50.0f, 0.0f)); walls[366]->setPos(Vec3(-86.0f, -50.0f, 0.0f));
walls[367]->setPos(Vec3(-85.0f, -50.0f, 0.0f)); walls[368]->setPos(Vec3(-84.0f, -50.0f, 0.0f));walls[369]->setPos(Vec3(-83.0f, -50.0f, 0.0f)); walls[370]->setPos(Vec3(-82.0f, -50.0f, 0.0f));
walls[371]->setPos(Vec3(-81.0f, -50.0f, 0.0f)); walls[372]->setPos(Vec3(-80.0f, -50.0f, 0.0f));walls[373]->setPos(Vec3(-79.0f, -50.0f, 0.0f)); walls[374]->setPos(Vec3(-78.0f, -50.0f, 0.0f));
walls[375]->setPos(Vec3(-77.0f, -50.0f, 0.0f)); walls[376]->setPos(Vec3(-76.0f, -50.0f, 0.0f));walls[377]->setPos(Vec3(-75.0f, -50.0f, 0.0f)); walls[378]->setPos(Vec3(-74.0f, -50.0f, 0.0f));
walls[379]->setPos(Vec3(-73.0f, -50.0f, 0.0f));	walls[380]->setPos(Vec3(-72.0f, -50.0f, 0.0f));walls[381]->setPos(Vec3(-71.0f, -50.0f, 0.0f)); walls[382]->setPos(Vec3(-70.0f, -50.0f, 0.0f));
walls[383]->setPos(Vec3(-69.0f, -50.0f, 0.0f)); walls[384]->setPos(Vec3(-68.0f, -50.0f, 0.0f));walls[385]->setPos(Vec3(-67.0f, -50.0f, 0.0f)); walls[386]->setPos(Vec3(-66.0f, -50.0f, 0.0f));
walls[387]->setPos(Vec3(-65.0f, -50.0f, 0.0f)); walls[388]->setPos(Vec3(-64.0f, -50.0f, 0.0f));walls[389]->setPos(Vec3(-63.0f, -50.0f, 0.0f)); walls[390]->setPos(Vec3(-62.0f, -50.0f, 0.0f));
walls[391]->setPos(Vec3(-61.0f, -50.0f, 0.0f)); walls[392]->setPos(Vec3(-60.0f, -50.0f, 0.0f));walls[393]->setPos(Vec3(-59.0f, -50.0f, 0.0f));	walls[394]->setPos(Vec3(-58.0f, -50.0f, 0.0f));
walls[395]->setPos(Vec3(-57.0f, -50.0f, 0.0f));	walls[396]->setPos(Vec3(-56.0f, -50.0f, 0.0f));walls[397]->setPos(Vec3(-55.0f, -50.0f, 0.0f)); walls[398]->setPos(Vec3(-54.0f, -50.0f, 0.0f));
walls[399]->setPos(Vec3(-53.0f, -50.0f, 0.0f));	walls[400]->setPos(Vec3(-52.0f, -50.0f, 0.0f));walls[401]->setPos(Vec3(-51.0f, -50.0f, 0.0f));	walls[402]->setPos(Vec3(-50.0f, -50.0f, 0.0f));
walls[403]->setPos(Vec3(-49.0f, -50.0f, 0.0f));	walls[404]->setPos(Vec3(-48.0f, -50.0f, 0.0f));walls[405]->setPos(Vec3(-47.0f, -50.0f, 0.0f));	walls[406]->setPos(Vec3(-46.0f, -50.0f, 0.0f));
walls[407]->setPos(Vec3(-45.0f, -50.0f, 0.0f));	walls[408]->setPos(Vec3(-44.0f, -50.0f, 0.0f));walls[409]->setPos(Vec3(-43.0f, -50.0f, 0.0f));	walls[410]->setPos(Vec3(-42.0f, -50.0f, 0.0f));	
walls[411]->setPos(Vec3(-41.0f, -50.0f, 0.0f));	walls[412]->setPos(Vec3(-40.0f, -50.0f, 0.0f));walls[413]->setPos(Vec3(-39.0f, -50.0f, 0.0f));	walls[414]->setPos(Vec3(-38.0f, -50.0f, 0.0f));
walls[415]->setPos(Vec3(-37.0f, -50.0f, 0.0f));	walls[416]->setPos(Vec3(-36.0f, -50.0f, 0.0f));walls[417]->setPos(Vec3(-35.0f, -50.0f, 0.0f)); walls[418]->setPos(Vec3(-34.0f, -50.0f, 0.0f));
walls[419]->setPos(Vec3(-33.0f, -50.0f, 0.0f));	walls[420]->setPos(Vec3(-32.0f, -50.0f, 0.0f));walls[421]->setPos(Vec3(-31.0f, -50.0f, 0.0f)); walls[422]->setPos(Vec3(-30.0f, -50.0f, 0.0f));		
walls[423]->setPos(Vec3(-29.0f, -50.0f, 0.0f));	walls[424]->setPos(Vec3(-28.0f, -50.0f, 0.0f));walls[425]->setPos(Vec3(-27.0f, -50.0f, 0.0f)); walls[426]->setPos(Vec3(-26.0f, -50.0f, 0.0f));
walls[427]->setPos(Vec3(-25.0f, -50.0f, 0.0f));	walls[428]->setPos(Vec3(-24.0f, -50.0f, 0.0f));walls[429]->setPos(Vec3(-23.0f, -50.0f, 0.0f));	walls[430]->setPos(Vec3(-22.0f, -50.0f, 0.0f));
walls[431]->setPos(Vec3(-21.0f, -50.0f, 0.0f));	walls[432]->setPos(Vec3(-20.0f, -50.0f, 0.0f));walls[433]->setPos(Vec3(-19.0f, -50.0f, 0.0f));	walls[434]->setPos(Vec3(-18.0f, -50.0f, 0.0f));
walls[435]->setPos(Vec3(-17.0f, -50.0f, 0.0f)); walls[436]->setPos(Vec3(-16.0f, -50.0f, 0.0f));walls[437]->setPos(Vec3(-15.0f, -50.0f, 0.0f)); walls[438]->setPos(Vec3(-14.0f, -50.0f, 0.0f));
walls[439]->setPos(Vec3(-13.0f, -50.0f, 0.0f)); walls[440]->setPos(Vec3(-12.0f, -50.0f, 0.0f));walls[441]->setPos(Vec3(-11.0f, -50.0f, 0.0f)); walls[442]->setPos(Vec3(-10.0f, -50.0f, 0.0f));
walls[443]->setPos(Vec3(-9.0f, -50.0f, 0.0f)); walls[444]->setPos(Vec3(-8.0f, -50.0f, 0.0f));walls[445]->setPos(Vec3(-7.0f, -50.0f, 0.0f)); walls[446]->setPos(Vec3(-6.0f, -50.0f, 0.0f));
walls[447]->setPos(Vec3(-5.0f, -50.0f, 0.0f)); walls[448]->setPos(Vec3(-4.0f, -50.0f, 0.0f));walls[449]->setPos(Vec3(-3.0f, -50.0f, 0.0f)); walls[450]->setPos(Vec3(-2.0f, -50.0f, 0.0f));
walls[451]->setPos(Vec3(-1.0f, -50.0f, 0.0f)); walls[452]->setPos(Vec3(0.0f, -50.0f, 0.0f));walls[453]->setPos(Vec3(1.0f, -50.0f, 0.0f)); walls[454]->setPos(Vec3(2.0f, -50.0f, 0.0f));
walls[455]->setPos(Vec3(3.0f, -50.0f, 0.0f)); walls[456]->setPos(Vec3(4.0f, -50.0f, 0.0f));walls[457]->setPos(Vec3(5.0f, -50.0f, 0.0f)); walls[458]->setPos(Vec3(6.0f, -50.0f, 0.0f));
walls[459]->setPos(Vec3(7.0f, -50.0f, 0.0f)); walls[460]->setPos(Vec3(8.0f, -50.0f, 0.0f));walls[461]->setPos(Vec3(9.0f, -50.0f, 0.0f)); walls[462]->setPos(Vec3(10.0f, -50.0f, 0.0f));
walls[463]->setPos(Vec3(11.0f, -50.0f, 0.0f)); walls[464]->setPos(Vec3(12.0f, -50.0f, 0.0f));walls[465]->setPos(Vec3(13.0f, -50.0f, 0.0f)); walls[466]->setPos(Vec3(14.0f, -50.0f, 0.0f));
walls[467]->setPos(Vec3(15.0f, -50.0f, 0.0f)); walls[468]->setPos(Vec3(16.0f, -50.0f, 0.0f));walls[469]->setPos(Vec3(17.0f, -50.0f, 0.0f)); walls[470]->setPos(Vec3(18.0f, -50.0f, 0.0f));
walls[471]->setPos(Vec3(19.0f, -50.0f, 0.0f)); walls[472]->setPos(Vec3(20.0f, -50.0f, 0.0f));walls[473]->setPos(Vec3(21.0f, -50.0f, 0.0f)); walls[474]->setPos(Vec3(22.0f, -50.0f, 0.0f));
walls[475]->setPos(Vec3(23.0f, -50.0f, 0.0f)); walls[476]->setPos(Vec3(24.0f, -50.0f, 0.0f));walls[477]->setPos(Vec3(25.0f, -50.0f, 0.0f)); walls[478]->setPos(Vec3(26.0f, -50.0f, 0.0f));
walls[479]->setPos(Vec3(27.0f, -50.0f, 0.0f)); walls[480]->setPos(Vec3(28.0f, -50.0f, 0.0f));walls[481]->setPos(Vec3(29.0f, -50.0f, 0.0f)); walls[482]->setPos(Vec3(30.0f, -50.0f, 0.0f));
walls[483]->setPos(Vec3(31.0f, -50.0f, 0.0f)); walls[484]->setPos(Vec3(32.0f, -50.0f, 0.0f));walls[485]->setPos(Vec3(33.0f, -50.0f, 0.0f)); walls[486]->setPos(Vec3(34.0f, -50.0f, 0.0f));
walls[487]->setPos(Vec3(35.0f, -50.0f, 0.0f)); walls[488]->setPos(Vec3(36.0f, -50.0f, 0.0f));walls[489]->setPos(Vec3(37.0f, -50.0f, 0.0f)); walls[490]->setPos(Vec3(38.0f, -50.0f, 0.0f));
walls[491]->setPos(Vec3(39.0f, -50.0f, 0.0f)); walls[492]->setPos(Vec3(40.0f, -50.0f, 0.0f));walls[493]->setPos(Vec3(41.0f, -50.0f, 0.0f)); walls[494]->setPos(Vec3(42.0f, -50.0f, 0.0f));
walls[495]->setPos(Vec3(43.0f, -50.0f, 0.0f)); walls[496]->setPos(Vec3(44.0f, -50.0f, 0.0f));walls[497]->setPos(Vec3(45.0f, -50.0f, 0.0f)); walls[498]->setPos(Vec3(46.0f, -50.0f, 0.0f));	
walls[499]->setPos(Vec3(47.0f, -50.0f, 0.0f)); walls[500]->setPos(Vec3(48.0f, -50.0f, 0.0f));walls[501]->setPos(Vec3(49.0f, -50.0f, 0.0f)); walls[502]->setPos(Vec3(50.0f, -50.0f, 0.0f));
walls[503]->setPos(Vec3(51.0f, -50.0f, 0.0f)); walls[504]->setPos(Vec3(52.0f, -50.0f, 0.0f));walls[505]->setPos(Vec3(53.0f, -50.0f, 0.0f)); walls[506]->setPos(Vec3(54.0f, -50.0f, 0.0f));
walls[507]->setPos(Vec3(55.0f, -50.0f, 0.0f)); walls[508]->setPos(Vec3(56.0f, -50.0f, 0.0f));walls[509]->setPos(Vec3(57.0f, -50.0f, 0.0f)); walls[510]->setPos(Vec3(58.0f, -50.0f, 0.0f));
walls[511]->setPos(Vec3(59.0f, -50.0f, 0.0f)); walls[512]->setPos(Vec3(60.0f, -50.0f, 0.0f));walls[513]->setPos(Vec3(61.0f, -50.0f, 0.0f)); walls[514]->setPos(Vec3(62.0f, -50.0f, 0.0f));
walls[515]->setPos(Vec3(63.0f, -50.0f, 0.0f)); walls[516]->setPos(Vec3(64.0f, -50.0f, 0.0f));walls[517]->setPos(Vec3(65.0f, -50.0f, 0.0f)); walls[518]->setPos(Vec3(66.0f, -50.0f, 0.0f));
walls[519]->setPos(Vec3(67.0f, -50.0f, 0.0f)); walls[520]->setPos(Vec3(68.0f, -50.0f, 0.0f));walls[521]->setPos(Vec3(69.0f, -50.0f, 0.0f)); walls[522]->setPos(Vec3(70.0f, -50.0f, 0.0f));
walls[523]->setPos(Vec3(71.0f, -50.0f, 0.0f)); walls[524]->setPos(Vec3(72.0f, -50.0f, 0.0f));walls[525]->setPos(Vec3(73.0f, -50.0f, 0.0f)); walls[526]->setPos(Vec3(74.0f, -50.0f, 0.0f));
walls[527]->setPos(Vec3(75.0f, -50.0f, 0.0f)); walls[528]->setPos(Vec3(76.0f, -50.0f, 0.0f));walls[529]->setPos(Vec3(77.0f, -50.0f, 0.0f)); walls[530]->setPos(Vec3(78.0f, -50.0f, 0.0f));
walls[531]->setPos(Vec3(79.0f, -50.0f, 0.0f)); walls[532]->setPos(Vec3(80.0f, -50.0f, 0.0f));walls[533]->setPos(Vec3(81.0f, -50.0f, 0.0f)); walls[534]->setPos(Vec3(82.0f, -50.0f, 0.0f));
walls[535]->setPos(Vec3(83.0f, -50.0f, 0.0f)); walls[536]->setPos(Vec3(84.0f, -50.0f, 0.0f));walls[537]->setPos(Vec3(85.0f, -50.0f, 0.0f)); walls[538]->setPos(Vec3(86.0f, -50.0f, 0.0f));
walls[539]->setPos(Vec3(87.0f, -50.0f, 0.0f)); walls[540]->setPos(Vec3(88.0f, -50.0f, 0.0f));walls[541]->setPos(Vec3(89.0f, -50.0f, 0.0f)); walls[542]->setPos(Vec3(90.0f, -50.0f, 0.0f));
walls[543]->setPos(Vec3(91.0f, -50.0f, 0.0f)); walls[544]->setPos(Vec3(92.0f, -50.0f, 0.0f));walls[545]->setPos(Vec3(93.0f, -50.0f, 0.0f)); walls[546]->setPos(Vec3(94.0f, -50.0f, 0.0f));
walls[547]->setPos(Vec3(95.0f, -50.0f, 0.0f)); walls[548]->setPos(Vec3(96.0f, -50.0f, 0.0f));walls[549]->setPos(Vec3(97.0f, -50.0f, 0.0f)); walls[550]->setPos(Vec3(98.0f, -50.0f, 0.0f));
walls[551]->setPos(Vec3(99.0f, -50.0f, 0.0f)); walls[552]->setPos(Vec3(100.0f, -50.0f, 0.0f));walls[553]->setPos(Vec3(101.0f, -50.0f, 0.0f)); walls[554]->setPos(Vec3(102.0f, -50.0f, 0.0f));
walls[555]->setPos(Vec3(103.0f, -50.0f, 0.0f));	walls[556]->setPos(Vec3(104.0f, -50.0f, 0.0f));walls[557]->setPos(Vec3(105.0f, -50.0f, 0.0f));	walls[558]->setPos(Vec3(106.0f, -50.0f, 0.0f));
walls[559]->setPos(Vec3(107.0f, -50.0f, 0.0f));	walls[560]->setPos(Vec3(108.0f, -50.0f, 0.0f));walls[561]->setPos(Vec3(109.0f, -50.0f, 0.0f));	walls[562]->setPos(Vec3(110.0f, -50.0f, 0.0f));
walls[563]->setPos(Vec3(111.0f, -50.0f, 0.0f)); walls[564]->setPos(Vec3(112.0f, -50.0f, 0.0f));walls[565]->setPos(Vec3(113.0f, -50.0f, 0.0f)); walls[566]->setPos(Vec3(114.0f, -50.0f, 0.0f));
walls[567]->setPos(Vec3(115.0f, -50.0f, 0.0f)); walls[568]->setPos(Vec3(116.0f, -50.0f, 0.0f));walls[569]->setPos(Vec3(117.0f, -50.0f, 0.0f)); walls[570]->setPos(Vec3(118.0f, -50.0f, 0.0f));
walls[571]->setPos(Vec3(119.0f, -50.0f, 0.0f)); walls[572]->setPos(Vec3(120.0f, -50.0f, 0.0f));walls[573]->setPos(Vec3(121.0f, -50.0f, 0.0f)); walls[574]->setPos(Vec3(122.0f, -50.0f, 0.0f));
walls[575]->setPos(Vec3(123.0f, -50.0f, 0.0f)); walls[576]->setPos(Vec3(124.0f, -50.0f, 0.0f));walls[577]->setPos(Vec3(125.0f, -50.0f, 0.0f)); walls[578]->setPos(Vec3(126.0f, -50.0f, 0.0f));
walls[579]->setPos(Vec3(127.0f, -50.0f, 0.0f)); walls[580]->setPos(Vec3(128.0f, -50.0f, 0.0f));walls[581]->setPos(Vec3(129.0f, -50.0f, 0.0f)); walls[582]->setPos(Vec3(130.0f, -50.0f, 0.0f));
walls[583]->setPos(Vec3(131.0f, -50.0f, 0.0f)); walls[584]->setPos(Vec3(132.0f, -50.0f, 0.0f));walls[585]->setPos(Vec3(133.0f, -50.0f, 0.0f)); walls[586]->setPos(Vec3(134.0f, -50.0f, 0.0f));
walls[587]->setPos(Vec3(135.0f, -50.0f, 0.0f)); walls[588]->setPos(Vec3(136.0f, -50.0f, 0.0f));walls[589]->setPos(Vec3(137.0f, -50.0f, 0.0f)); walls[590]->setPos(Vec3(138.0f, -50.0f, 0.0f));
walls[591]->setPos(Vec3(139.0f, -50.0f, 0.0f)); walls[592]->setPos(Vec3(140.0f, -50.0f, 0.0f));walls[593]->setPos(Vec3(141.0f, -50.0f, 0.0f)); walls[594]->setPos(Vec3(142.0f, -50.0f, 0.0f));
walls[595]->setPos(Vec3(143.0f, -50.0f, 0.0f));	walls[596]->setPos(Vec3(144.0f, -50.0f, 0.0f));walls[597]->setPos(Vec3(145.0f, -50.0f, 0.0f));	walls[598]->setPos(Vec3(146.0f, -50.0f, 0.0f));
walls[599]->setPos(Vec3(147.0f, -50.0f, 0.0f)); walls[600]->setPos(Vec3(148.0f, -50.0f, 0.0f));walls[601]->setPos(Vec3(149.0f, -50.0f, 0.0f)); walls[602]->setPos(Vec3(150.0f, -50.0f, 0.0f));
walls[603]->setPos(Vec3(151.0f, -50.0f, 0.0f)); walls[604]->setPos(Vec3(152.0f, -50.0f, 0.0f));walls[605]->setPos(Vec3(153.0f, -50.0f, 0.0f)); walls[606]->setPos(Vec3(154.0f, -50.0f, 0.0f));
walls[607]->setPos(Vec3(155.0f, -50.0f, 0.0f)); walls[608]->setPos(Vec3(156.0f, -50.0f, 0.0f));walls[609]->setPos(Vec3(157.0f, -50.0f, 0.0f)); walls[610]->setPos(Vec3(158.0f, -50.0f, 0.0f));
walls[611]->setPos(Vec3(159.0f, -50.0f, 0.0f)); walls[612]->setPos(Vec3(160.0f, -50.0f, 0.0f));walls[613]->setPos(Vec3(161.0f, -50.0f, 0.0f)); walls[614]->setPos(Vec3(162.0f, -50.0f, 0.0f));
walls[615]->setPos(Vec3(163.0f, -50.0f, 0.0f));	walls[616]->setPos(Vec3(164.0f, -50.0f, 0.0f));walls[617]->setPos(Vec3(165.0f, -50.0f, 0.0f)); walls[618]->setPos(Vec3(166.0f, -50.0f, 0.0f));
walls[619]->setPos(Vec3(167.0f, -50.0f, 0.0f)); walls[620]->setPos(Vec3(168.0f, -50.0f, 0.0f));walls[621]->setPos(Vec3(169.0f, -50.0f, 0.0f));	walls[622]->setPos(Vec3(170.0f, -50.0f, 0.0f));
walls[623]->setPos(Vec3(171.0f, -50.0f, 0.0f));	walls[624]->setPos(Vec3(172.0f, -50.0f, 0.0f));walls[625]->setPos(Vec3(173.0f, -50.0f, 0.0f)); walls[626]->setPos(Vec3(174.0f, -50.0f, 0.0f));
walls[627]->setPos(Vec3(175.0f, -50.0f, 0.0f));	walls[628]->setPos(Vec3(176.0f, -50.0f, 0.0f));walls[629]->setPos(Vec3(177.0f, -50.0f, 0.0f));	walls[630]->setPos(Vec3(178.0f, -50.0f, 0.0f));
walls[631]->setPos(Vec3(179.0f, -50.0f, 0.0f));	walls[632]->setPos(Vec3(180.0f, -50.0f, 0.0f));walls[633]->setPos(Vec3(181.0f, -50.0f, 0.0f));	walls[634]->setPos(Vec3(182.0f, -50.0f, 0.0f));
walls[635]->setPos(Vec3(183.0f, -50.0f, 0.0f));	walls[636]->setPos(Vec3(184.0f, -50.0f, 0.0f));walls[637]->setPos(Vec3(185.0f, -50.0f, 0.0f));	walls[638]->setPos(Vec3(186.0f, -50.0f, 0.0f));
walls[639]->setPos(Vec3(187.0f, -50.0f, 0.0f));	walls[640]->setPos(Vec3(188.0f, -50.0f, 0.0f));walls[641]->setPos(Vec3(189.0f, -50.0f, 0.0f));	walls[642]->setPos(Vec3(190.0f, -50.0f, 0.0f));
walls[643]->setPos(Vec3(191.0f, -50.0f, 0.0f));	walls[644]->setPos(Vec3(192.0f, -50.0f, 0.0f));walls[645]->setPos(Vec3(193.0f, -50.0f, 0.0f));	walls[646]->setPos(Vec3(194.0f, -50.0f, 0.0f));
walls[647]->setPos(Vec3(195.0f, -50.0f, 0.0f));	walls[648]->setPos(Vec3(196.0f, -50.0f, 0.0f));walls[649]->setPos(Vec3(197.0f, -50.0f, 0.0f));	walls[650]->setPos(Vec3(198.0f, -50.0f, 0.0f));
walls[651]->setPos(Vec3(199.0f, -50.0f, 0.0f));	walls[652]->setPos(Vec3(200.0f, -50.0f, 0.0f));walls[653]->setPos(Vec3(201.0f, -50.0f, 0.0f));	walls[654]->setPos(Vec3(202.0f, -50.0f, 0.0f));
walls[655]->setPos(Vec3(203.0f, -50.0f, 0.0f));	walls[656]->setPos(Vec3(204.0f, -50.0f, 0.0f));walls[657]->setPos(Vec3(205.0f, -50.0f, 0.0f));	walls[658]->setPos(Vec3(206.0f, -50.0f, 0.0f));
walls[659]->setPos(Vec3(207.0f, -50.0f, 0.0f));	walls[660]->setPos(Vec3(208.0f, -50.0f, 0.0f));walls[661]->setPos(Vec3(209.0f, -50.0f, 0.0f));	walls[662]->setPos(Vec3(210.0f, -50.0f, 0.0f));
walls[663]->setPos(Vec3(211.0f, -50.0f, 0.0f));	walls[664]->setPos(Vec3(212.0f, -50.0f, 0.0f));walls[665]->setPos(Vec3(213.0f, -50.0f, 0.0f));	walls[666]->setPos(Vec3(214.0f, -50.0f, 0.0f));
walls[667]->setPos(Vec3(215.0f, -50.0f, 0.0f));	walls[668]->setPos(Vec3(216.0f, -50.0f, 0.0f));walls[669]->setPos(Vec3(217.0f, -50.0f, 0.0f));	walls[670]->setPos(Vec3(218.0f, -50.0f, 0.0f));
walls[671]->setPos(Vec3(219.0f, -50.0f, 0.0f)); walls[672]->setPos(Vec3(220.0f, -50.0f, 0.0f));walls[673]->setPos(Vec3(221.0f, -50.0f, 0.0f));	walls[674]->setPos(Vec3(222.0f, -50.0f, 0.0f));
walls[675]->setPos(Vec3(223.0f, -50.0f, 0.0f));	walls[676]->setPos(Vec3(224.0f, -50.0f, 0.0f));walls[677]->setPos(Vec3(225.0f, -50.0f, 0.0f));	walls[678]->setPos(Vec3(226.0f, -50.0f, 0.0f));
walls[679]->setPos(Vec3(227.0f, -50.0f, 0.0f));	walls[680]->setPos(Vec3(228.0f, -50.0f, 0.0f));walls[681]->setPos(Vec3(229.0f, -50.0f, 0.0f));	walls[682]->setPos(Vec3(230.0f, -50.0f, 0.0f));
walls[683]->setPos(Vec3(231.0f, -50.0f, 0.0f)); walls[684]->setPos(Vec3(232.0f, -50.0f, 0.0f));walls[685]->setPos(Vec3(233.0f, -50.0f, 0.0f)); walls[686]->setPos(Vec3(234.0f, -50.0f, 0.0f));
walls[687]->setPos(Vec3(235.0f, -50.0f, 0.0f));	walls[688]->setPos(Vec3(236.0f, -50.0f, 0.0f));walls[689]->setPos(Vec3(237.0f, -50.0f, 0.0f));	walls[690]->setPos(Vec3(238.0f, -50.0f, 0.0f));
walls[691]->setPos(Vec3(239.0f, -50.0f, 0.0f));	walls[692]->setPos(Vec3(240.0f, -50.0f, 0.0f));walls[693]->setPos(Vec3(241.0f, -50.0f, 0.0f));	walls[694]->setPos(Vec3(242.0f, -50.0f, 0.0f));
walls[695]->setPos(Vec3(243.0f, -50.0f, 0.0f));	walls[696]->setPos(Vec3(244.0f, -50.0f, 0.0f));walls[697]->setPos(Vec3(245.0f, -50.0f, 0.0f)); walls[698]->setPos(Vec3(246.0f, -50.0f, 0.0f));
walls[699]->setPos(Vec3(247.0f, -50.0f, 0.0f));	walls[700]->setPos(Vec3(248.0f, -50.0f, 0.0f));walls[701]->setPos(Vec3(249.0f, -50.0f, 0.0f));
#pragma endregion

#pragma region topwall	
		//top wall
walls[702]->setPos(Vec3(-249.0f, 50.0f, 0.0f)); walls[703]->setPos(Vec3(-248.0f, 50.0f, 0.0f));walls[704]->setPos(Vec3(-247.0f, 50.0f, 0.0f)); walls[705]->setPos(Vec3(-246.0f, 50.0f, 0.0f));	
walls[706]->setPos(Vec3(-245.0f, 50.0f, 0.0f)); walls[707]->setPos(Vec3(-244.0f, 50.0f, 0.0f));walls[708]->setPos(Vec3(-243.0f, 50.0f, 0.0f)); walls[709]->setPos(Vec3(-242.0f, 50.0f, 0.0f));
walls[710]->setPos(Vec3(-241.0f, 50.0f, 0.0f)); walls[711]->setPos(Vec3(-240.0f, 50.0f, 0.0f));walls[712]->setPos(Vec3(-239.0f, 50.0f, 0.0f)); walls[713]->setPos(Vec3(-238.0f, 50.0f, 0.0f));
walls[714]->setPos(Vec3(-237.0f, 50.0f, 0.0f)); walls[715]->setPos(Vec3(-236.0f, 50.0f, 0.0f));walls[716]->setPos(Vec3(-235.0f, 50.0f, 0.0f)); walls[717]->setPos(Vec3(-234.0f, 50.0f, 0.0f));
walls[718]->setPos(Vec3(-233.0f, 50.0f, 0.0f)); walls[719]->setPos(Vec3(-232.0f, 50.0f, 0.0f));walls[720]->setPos(Vec3(-231.0f, 50.0f, 0.0f)); walls[721]->setPos(Vec3(-230.0f, 50.0f, 0.0f));
walls[722]->setPos(Vec3(-229.0f, 50.0f, 0.0f)); walls[723]->setPos(Vec3(-228.0f, 50.0f, 0.0f));walls[724]->setPos(Vec3(-227.0f, 50.0f, 0.0f)); walls[725]->setPos(Vec3(-226.0f, 50.0f, 0.0f));
walls[726]->setPos(Vec3(-225.0f, 50.0f, 0.0f)); walls[727]->setPos(Vec3(-224.0f, 50.0f, 0.0f));walls[728]->setPos(Vec3(-223.0f, 50.0f, 0.0f)); walls[729]->setPos(Vec3(-222.0f, 50.0f, 0.0f));
walls[730]->setPos(Vec3(-221.0f, 50.0f, 0.0f)); walls[731]->setPos(Vec3(-220.0f, 50.0f, 0.0f));walls[732]->setPos(Vec3(-219.0f, 50.0f, 0.0f));	walls[733]->setPos(Vec3(-218.0f, 50.0f, 0.0f));
walls[734]->setPos(Vec3(-217.0f, 50.0f, 0.0f)); walls[735]->setPos(Vec3(-216.0f, 50.0f, 0.0f));walls[736]->setPos(Vec3(-215.0f, 50.0f, 0.0f)); walls[737]->setPos(Vec3(-214.0f, 50.0f, 0.0f));
walls[738]->setPos(Vec3(-213.0f, 50.0f, 0.0f)); walls[739]->setPos(Vec3(-212.0f, 50.0f, 0.0f));walls[740]->setPos(Vec3(-211.0f, 50.0f, 0.0f)); walls[741]->setPos(Vec3(-210.0f, 50.0f, 0.0f));
walls[742]->setPos(Vec3(-209.0f, 50.0f, 0.0f)); walls[743]->setPos(Vec3(-208.0f, 50.0f, 0.0f));walls[744]->setPos(Vec3(-207.0f, 50.0f, 0.0f)); walls[745]->setPos(Vec3(-206.0f, 50.0f, 0.0f));
walls[746]->setPos(Vec3(-205.0f, 50.0f, 0.0f)); walls[747]->setPos(Vec3(-204.0f, 50.0f, 0.0f));walls[748]->setPos(Vec3(-203.0f, 50.0f, 0.0f)); walls[749]->setPos(Vec3(-202.0f, 50.0f, 0.0f));
walls[750]->setPos(Vec3(-201.0f, 50.0f, 0.0f)); walls[751]->setPos(Vec3(-200.0f, 50.0f, 0.0f));walls[752]->setPos(Vec3(-199.0f, 50.0f, 0.0f)); walls[753]->setPos(Vec3(-198.0f, 50.0f, 0.0f));
walls[754]->setPos(Vec3(-197.0f, 50.0f, 0.0f)); walls[755]->setPos(Vec3(-196.0f, 50.0f, 0.0f));walls[756]->setPos(Vec3(-195.0f, 50.0f, 0.0f)); walls[757]->setPos(Vec3(-194.0f, 50.0f, 0.0f));
walls[758]->setPos(Vec3(-193.0f, 50.0f, 0.0f));	walls[759]->setPos(Vec3(-192.0f, 50.0f, 0.0f));walls[760]->setPos(Vec3(-191.0f, 50.0f, 0.0f)); walls[761]->setPos(Vec3(-190.0f, 50.0f, 0.0f));
walls[762]->setPos(Vec3(-189.0f, 50.0f, 0.0f)); walls[763]->setPos(Vec3(-188.0f, 50.0f, 0.0f));walls[764]->setPos(Vec3(-187.0f, 50.0f, 0.0f)); walls[765]->setPos(Vec3(-186.0f, 50.0f, 0.0f));
walls[766]->setPos(Vec3(-185.0f, 50.0f, 0.0f)); walls[767]->setPos(Vec3(-184.0f, 50.0f, 0.0f));walls[768]->setPos(Vec3(-183.0f, 50.0f, 0.0f)); walls[769]->setPos(Vec3(-182.0f, 50.0f, 0.0f));
walls[770]->setPos(Vec3(-181.0f, 50.0f, 0.0f)); walls[771]->setPos(Vec3(-180.0f, 50.0f, 0.0f));walls[772]->setPos(Vec3(-179.0f, 50.0f, 0.0f)); walls[773]->setPos(Vec3(-178.0f, 50.0f, 0.0f));
walls[774]->setPos(Vec3(-177.0f, 50.0f, 0.0f)); walls[775]->setPos(Vec3(-176.0f, 50.0f, 0.0f));walls[776]->setPos(Vec3(-175.0f, 50.0f, 0.0f)); walls[777]->setPos(Vec3(-174.0f, 50.0f, 0.0f));
walls[778]->setPos(Vec3(-173.0f, 50.0f, 0.0f)); walls[779]->setPos(Vec3(-172.0f, 50.0f, 0.0f));walls[780]->setPos(Vec3(-171.0f, 50.0f, 0.0f)); walls[781]->setPos(Vec3(-170.0f, 50.0f, 0.0f));
walls[782]->setPos(Vec3(-169.0f, 50.0f, 0.0f)); walls[783]->setPos(Vec3(-168.0f, 50.0f, 0.0f));walls[784]->setPos(Vec3(-167.0f, 50.0f, 0.0f)); walls[785]->setPos(Vec3(-166.0f, 50.0f, 0.0f));
walls[786]->setPos(Vec3(-165.0f, 50.0f, 0.0f)); walls[787]->setPos(Vec3(-164.0f, 50.0f, 0.0f));walls[788]->setPos(Vec3(-163.0f, 50.0f, 0.0f)); walls[789]->setPos(Vec3(-162.0f, 50.0f, 0.0f));
walls[790]->setPos(Vec3(-161.0f, 50.0f, 0.0f)); walls[791]->setPos(Vec3(-160.0f, 50.0f, 0.0f));walls[792]->setPos(Vec3(-159.0f, 50.0f, 0.0f)); walls[793]->setPos(Vec3(-158.0f, 50.0f, 0.0f));
walls[794]->setPos(Vec3(-157.0f, 50.0f, 0.0f)); walls[795]->setPos(Vec3(-156.0f, 50.0f, 0.0f));walls[796]->setPos(Vec3(-155.0f, 50.0f, 0.0f)); walls[797]->setPos(Vec3(-154.0f, 50.0f, 0.0f));
walls[798]->setPos(Vec3(-153.0f, 50.0f, 0.0f)); walls[799]->setPos(Vec3(-152.0f, 50.0f, 0.0f));walls[800]->setPos(Vec3(-151.0f, 50.0f, 0.0f)); walls[801]->setPos(Vec3(-150.0f, 50.0f, 0.0f));
walls[802]->setPos(Vec3(-149.0f, 50.0f, 0.0f));	walls[803]->setPos(Vec3(-148.0f, 50.0f, 0.0f));walls[804]->setPos(Vec3(-147.0f, 50.0f, 0.0f)); walls[805]->setPos(Vec3(-146.0f, 50.0f, 0.0f));
walls[806]->setPos(Vec3(-145.0f, 50.0f, 0.0f)); walls[807]->setPos(Vec3(-144.0f, 50.0f, 0.0f));walls[808]->setPos(Vec3(-143.0f, 50.0f, 0.0f));	walls[809]->setPos(Vec3(-142.0f, 50.0f, 0.0f));
walls[810]->setPos(Vec3(-141.0f, 50.0f, 0.0f)); walls[811]->setPos(Vec3(-140.0f, 50.0f, 0.0f));walls[812]->setPos(Vec3(-139.0f, 50.0f, 0.0f)); walls[813]->setPos(Vec3(-138.0f, 50.0f, 0.0f));
walls[814]->setPos(Vec3(-137.0f, 50.0f, 0.0f)); walls[815]->setPos(Vec3(-136.0f, 50.0f, 0.0f));walls[816]->setPos(Vec3(-135.0f, 50.0f, 0.0f)); walls[817]->setPos(Vec3(-134.0f, 50.0f, 0.0f));
walls[818]->setPos(Vec3(-133.0f, 50.0f, 0.0f)); walls[819]->setPos(Vec3(-132.0f, 50.0f, 0.0f));walls[820]->setPos(Vec3(-131.0f, 50.0f, 0.0f));	walls[821]->setPos(Vec3(-130.0f, 50.0f, 0.0f));
walls[822]->setPos(Vec3(-129.0f, 50.0f, 0.0f)); walls[823]->setPos(Vec3(-128.0f, 50.0f, 0.0f));walls[824]->setPos(Vec3(-127.0f, 50.0f, 0.0f));	walls[825]->setPos(Vec3(-126.0f, 50.0f, 0.0f));
walls[826]->setPos(Vec3(-125.0f, 50.0f, 0.0f)); walls[827]->setPos(Vec3(-124.0f, 50.0f, 0.0f));walls[828]->setPos(Vec3(-123.0f, 50.0f, 0.0f)); walls[829]->setPos(Vec3(-122.0f, 50.0f, 0.0f));
walls[830]->setPos(Vec3(-121.0f, 50.0f, 0.0f)); walls[831]->setPos(Vec3(-120.0f, 50.0f, 0.0f));walls[832]->setPos(Vec3(-119.0f, 50.0f, 0.0f)); walls[833]->setPos(Vec3(-118.0f, 50.0f, 0.0f));
walls[834]->setPos(Vec3(-117.0f, 50.0f, 0.0f)); walls[835]->setPos(Vec3(-116.0f, 50.0f, 0.0f));walls[836]->setPos(Vec3(-115.0f, 50.0f, 0.0f)); walls[837]->setPos(Vec3(-114.0f, 50.0f, 0.0f));
walls[838]->setPos(Vec3(-113.0f, 50.0f, 0.0f)); walls[839]->setPos(Vec3(-112.0f, 50.0f, 0.0f));walls[840]->setPos(Vec3(-111.0f, 50.0f, 0.0f)); walls[841]->setPos(Vec3(-110.0f, 50.0f, 0.0f));
walls[842]->setPos(Vec3(-109.0f, 50.0f, 0.0f)); walls[843]->setPos(Vec3(-108.0f, 50.0f, 0.0f));walls[844]->setPos(Vec3(-107.0f, 50.0f, 0.0f)); walls[845]->setPos(Vec3(-106.0f, 50.0f, 0.0f));
walls[846]->setPos(Vec3(-105.0f, 50.0f, 0.0f)); walls[847]->setPos(Vec3(-104.0f, 50.0f, 0.0f));walls[848]->setPos(Vec3(-103.0f, 50.0f, 0.0f)); walls[849]->setPos(Vec3(-102.0f, 50.0f, 0.0f));
walls[850]->setPos(Vec3(-101.0f, 50.0f, 0.0f)); walls[851]->setPos(Vec3(-100.0f, 50.0f, 0.0f));walls[852]->setPos(Vec3(-99.0f, 50.0f, 0.0f)); walls[853]->setPos(Vec3(-98.0f, 50.0f, 0.0f));
walls[854]->setPos(Vec3(-97.0f, 50.0f, 0.0f)); walls[855]->setPos(Vec3(-96.0f, 50.0f, 0.0f));walls[856]->setPos(Vec3(-95.0f, 50.0f, 0.0f)); walls[857]->setPos(Vec3(-94.0f, 50.0f, 0.0f));
walls[858]->setPos(Vec3(-93.0f, 50.0f, 0.0f)); walls[859]->setPos(Vec3(-92.0f, 50.0f, 0.0f));walls[860]->setPos(Vec3(-91.0f, 50.0f, 0.0f)); walls[861]->setPos(Vec3(-90.0f, 50.0f, 0.0f));
walls[862]->setPos(Vec3(-89.0f, 50.0f, 0.0f)); walls[863]->setPos(Vec3(-88.0f, 50.0f, 0.0f));walls[864]->setPos(Vec3(-87.0f, 50.0f, 0.0f)); walls[865]->setPos(Vec3(-86.0f, 50.0f, 0.0f));
walls[866]->setPos(Vec3(-85.0f, 50.0f, 0.0f)); walls[867]->setPos(Vec3(-84.0f, 50.0f, 0.0f));walls[868]->setPos(Vec3(-83.0f, 50.0f, 0.0f)); walls[869]->setPos(Vec3(-82.0f, 50.0f, 0.0f));
walls[870]->setPos(Vec3(-81.0f, 50.0f, 0.0f)); walls[871]->setPos(Vec3(-80.0f, 50.0f, 0.0f));walls[872]->setPos(Vec3(-79.0f, 50.0f, 0.0f)); walls[873]->setPos(Vec3(-78.0f, 50.0f, 0.0f));
walls[874]->setPos(Vec3(-77.0f, 50.0f, 0.0f)); walls[875]->setPos(Vec3(-76.0f, 50.0f, 0.0f));walls[876]->setPos(Vec3(-75.0f, 50.0f, 0.0f)); walls[877]->setPos(Vec3(-74.0f, 50.0f, 0.0f));
walls[878]->setPos(Vec3(-73.0f, 50.0f, 0.0f)); walls[879]->setPos(Vec3(-72.0f, 50.0f, 0.0f));walls[880]->setPos(Vec3(-71.0f, 50.0f, 0.0f)); walls[881]->setPos(Vec3(-70.0f, 50.0f, 0.0f));
walls[882]->setPos(Vec3(-69.0f, 50.0f, 0.0f)); walls[883]->setPos(Vec3(-68.0f, 50.0f, 0.0f));walls[884]->setPos(Vec3(-67.0f, 50.0f, 0.0f)); walls[885]->setPos(Vec3(-66.0f, 50.0f, 0.0f));
walls[886]->setPos(Vec3(-65.0f, 50.0f, 0.0f)); walls[887]->setPos(Vec3(-64.0f, 50.0f, 0.0f));walls[888]->setPos(Vec3(-63.0f, 50.0f, 0.0f)); walls[889]->setPos(Vec3(-62.0f, 50.0f, 0.0f));
walls[890]->setPos(Vec3(-61.0f, 50.0f, 0.0f)); walls[891]->setPos(Vec3(-60.0f, 50.0f, 0.0f));walls[892]->setPos(Vec3(-59.0f, 50.0f, 0.0f)); walls[893]->setPos(Vec3(-58.0f, 50.0f, 0.0f));
walls[894]->setPos(Vec3(-57.0f, 50.0f, 0.0f)); walls[895]->setPos(Vec3(-56.0f, 50.0f, 0.0f));walls[896]->setPos(Vec3(-55.0f, 50.0f, 0.0f)); walls[897]->setPos(Vec3(-54.0f, 50.0f, 0.0f));
walls[898]->setPos(Vec3(-53.0f, 50.0f, 0.0f)); walls[899]->setPos(Vec3(-52.0f, 50.0f, 0.0f));walls[900]->setPos(Vec3(-51.0f, 50.0f, 0.0f)); walls[901]->setPos(Vec3(-50.0f, 50.0f, 0.0f));
walls[902]->setPos(Vec3(-49.0f, 50.0f, 0.0f)); walls[903]->setPos(Vec3(-48.0f, 50.0f, 0.0f));walls[904]->setPos(Vec3(-47.0f, 50.0f, 0.0f)); walls[905]->setPos(Vec3(-46.0f, 50.0f, 0.0f));
walls[906]->setPos(Vec3(-45.0f, 50.0f, 0.0f)); walls[907]->setPos(Vec3(-44.0f, 50.0f, 0.0f));walls[908]->setPos(Vec3(-43.0f, 50.0f, 0.0f)); walls[910]->setPos(Vec3(-42.0f, 50.0f, 0.0f));
walls[911]->setPos(Vec3(-41.0f, 50.0f, 0.0f)); walls[912]->setPos(Vec3(-40.0f, 50.0f, 0.0f));walls[913]->setPos(Vec3(-39.0f, 50.0f, 0.0f)); walls[914]->setPos(Vec3(-38.0f, 50.0f, 0.0f));
walls[915]->setPos(Vec3(-37.0f, 50.0f, 0.0f)); walls[916]->setPos(Vec3(-36.0f, 50.0f, 0.0f));walls[917]->setPos(Vec3(-35.0f, 50.0f, 0.0f)); walls[918]->setPos(Vec3(-34.0f, 50.0f, 0.0f));
walls[919]->setPos(Vec3(-33.0f, 50.0f, 0.0f)); walls[920]->setPos(Vec3(-32.0f, 50.0f, 0.0f));walls[921]->setPos(Vec3(-31.0f, 50.0f, 0.0f)); walls[922]->setPos(Vec3(-30.0f, 50.0f, 0.0f));
walls[923]->setPos(Vec3(-29.0f, 50.0f, 0.0f)); walls[924]->setPos(Vec3(-28.0f, 50.0f, 0.0f));walls[925]->setPos(Vec3(-27.0f, 50.0f, 0.0f)); walls[926]->setPos(Vec3(-26.0f, 50.0f, 0.0f));
walls[927]->setPos(Vec3(-25.0f, 50.0f, 0.0f)); walls[928]->setPos(Vec3(-24.0f, 50.0f, 0.0f));walls[929]->setPos(Vec3(-23.0f, 50.0f, 0.0f)); walls[930]->setPos(Vec3(-22.0f, 50.0f, 0.0f));
walls[931]->setPos(Vec3(-21.0f, 50.0f, 0.0f)); walls[932]->setPos(Vec3(-20.0f, 50.0f, 0.0f));walls[933]->setPos(Vec3(-19.0f, 50.0f, 0.0f)); walls[934]->setPos(Vec3(-18.0f, 50.0f, 0.0f));
walls[935]->setPos(Vec3(-17.0f, 50.0f, 0.0f)); walls[936]->setPos(Vec3(-16.0f, 50.0f, 0.0f));walls[937]->setPos(Vec3(-15.0f, 50.0f, 0.0f)); walls[938]->setPos(Vec3(-14.0f, 50.0f, 0.0f));
walls[939]->setPos(Vec3(-13.0f, 50.0f, 0.0f)); walls[940]->setPos(Vec3(-12.0f, 50.0f, 0.0f));walls[941]->setPos(Vec3(-11.0f, 50.0f, 0.0f)); walls[942]->setPos(Vec3(-10.0f, 50.0f, 0.0f));
walls[943]->setPos(Vec3(-9.0f, 50.0f, 0.0f)); walls[944]->setPos(Vec3(-8.0f, 50.0f, 0.0f));walls[945]->setPos(Vec3(-7.0f, 50.0f, 0.0f)); walls[946]->setPos(Vec3(-6.0f, 50.0f, 0.0f));
walls[947]->setPos(Vec3(-5.0f, 50.0f, 0.0f)); walls[948]->setPos(Vec3(-4.0f, 50.0f, 0.0f));walls[949]->setPos(Vec3(-3.0f, 50.0f, 0.0f)); walls[950]->setPos(Vec3(-2.0f, 50.0f, 0.0f));
walls[951]->setPos(Vec3(-1.0f, 50.0f, 0.0f)); walls[952]->setPos(Vec3(0.0f, 50.0f, 0.0f));walls[953]->setPos(Vec3(1.0f, 50.0f, 0.0f)); walls[954]->setPos(Vec3(2.0f, 50.0f, 0.0f));
walls[955]->setPos(Vec3(3.0f, 50.0f, 0.0f)); walls[956]->setPos(Vec3(4.0f, 50.0f, 0.0f)); walls[957]->setPos(Vec3(5.0f, 50.0f, 0.0f)); walls[958]->setPos(Vec3(6.0f, 50.0f, 0.0f));
walls[959]->setPos(Vec3(7.0f, 50.0f, 0.0f)); walls[960]->setPos(Vec3(8.0f, 50.0f, 0.0f)); walls[961]->setPos(Vec3(9.0f, 50.0f, 0.0f)); walls[962]->setPos(Vec3(10.0f, 50.0f, 0.0f));
walls[963]->setPos(Vec3(11.0f, 50.0f, 0.0f)); walls[964]->setPos(Vec3(12.0f, 50.0f, 0.0f));walls[965]->setPos(Vec3(13.0f, 50.0f, 0.0f)); walls[966]->setPos(Vec3(14.0f, 50.0f, 0.0f));
walls[967]->setPos(Vec3(15.0f, 50.0f, 0.0f)); walls[968]->setPos(Vec3(16.0f, 50.0f, 0.0f));walls[969]->setPos(Vec3(17.0f, 50.0f, 0.0f)); walls[970]->setPos(Vec3(18.0f, 50.0f, 0.0f));
walls[971]->setPos(Vec3(19.0f, 50.0f, 0.0f)); walls[972]->setPos(Vec3(20.0f, 50.0f, 0.0f));walls[973]->setPos(Vec3(21.0f, 50.0f, 0.0f)); walls[974]->setPos(Vec3(22.0f, 50.0f, 0.0f));
walls[975]->setPos(Vec3(23.0f, 50.0f, 0.0f)); walls[976]->setPos(Vec3(24.0f, 50.0f, 0.0f));walls[977]->setPos(Vec3(25.0f, 50.0f, 0.0f)); walls[978]->setPos(Vec3(26.0f, 50.0f, 0.0f));
walls[979]->setPos(Vec3(27.0f, 50.0f, 0.0f)); walls[980]->setPos(Vec3(28.0f, 50.0f, 0.0f));walls[981]->setPos(Vec3(29.0f, 50.0f, 0.0f)); walls[982]->setPos(Vec3(30.0f, 50.0f, 0.0f));
walls[983]->setPos(Vec3(31.0f, 50.0f, 0.0f)); walls[984]->setPos(Vec3(32.0f, 50.0f, 0.0f));walls[985]->setPos(Vec3(33.0f, 50.0f, 0.0f)); walls[986]->setPos(Vec3(34.0f, 50.0f, 0.0f));
walls[987]->setPos(Vec3(35.0f, 50.0f, 0.0f)); walls[988]->setPos(Vec3(36.0f, 50.0f, 0.0f));walls[989]->setPos(Vec3(37.0f, 50.0f, 0.0f)); walls[990]->setPos(Vec3(38.0f, 50.0f, 0.0f));
walls[991]->setPos(Vec3(39.0f, 50.0f, 0.0f)); walls[992]->setPos(Vec3(40.0f, 50.0f, 0.0f));walls[993]->setPos(Vec3(41.0f, 50.0f, 0.0f)); walls[994]->setPos(Vec3(42.0f, 50.0f, 0.0f));
walls[995]->setPos(Vec3(43.0f, 50.0f, 0.0f)); walls[996]->setPos(Vec3(44.0f, 50.0f, 0.0f));walls[997]->setPos(Vec3(45.0f, 50.0f, 0.0f)); walls[998]->setPos(Vec3(46.0f, 50.0f, 0.0f));
walls[999]->setPos(Vec3(47.0f, 50.0f, 0.0f)); walls[1000]->setPos(Vec3(48.0f, 50.0f, 0.0f));walls[1001]->setPos(Vec3(49.0f, 50.0f, 0.0f)); walls[1002]->setPos(Vec3(50.0f, 50.0f, 0.0f));
walls[1003]->setPos(Vec3(51.0f, 50.0f, 0.0f)); walls[1004]->setPos(Vec3(52.0f, 50.0f, 0.0f));walls[1005]->setPos(Vec3(53.0f, 50.0f, 0.0f)); walls[1006]->setPos(Vec3(54.0f, 50.0f, 0.0f));
walls[1007]->setPos(Vec3(55.0f, 50.0f, 0.0f)); walls[1008]->setPos(Vec3(56.0f, 50.0f, 0.0f));walls[1009]->setPos(Vec3(57.0f, 50.0f, 0.0f)); walls[1010]->setPos(Vec3(58.0f, 50.0f, 0.0f));
walls[1011]->setPos(Vec3(59.0f, 50.0f, 0.0f)); walls[1012]->setPos(Vec3(60.0f, 50.0f, 0.0f));walls[1013]->setPos(Vec3(61.0f, 50.0f, 0.0f)); walls[1014]->setPos(Vec3(62.0f, 50.0f, 0.0f));
walls[1015]->setPos(Vec3(63.0f, 50.0f, 0.0f)); walls[1016]->setPos(Vec3(64.0f, 50.0f, 0.0f));walls[1017]->setPos(Vec3(65.0f, 50.0f, 0.0f)); walls[1018]->setPos(Vec3(66.0f, 50.0f, 0.0f));
walls[1019]->setPos(Vec3(67.0f, 50.0f, 0.0f)); walls[1020]->setPos(Vec3(68.0f, 50.0f, 0.0f));walls[1021]->setPos(Vec3(69.0f, 50.0f, 0.0f)); walls[1022]->setPos(Vec3(70.0f, 50.0f, 0.0f));
walls[1023]->setPos(Vec3(71.0f, 50.0f, 0.0f)); walls[1024]->setPos(Vec3(72.0f, 50.0f, 0.0f));walls[1025]->setPos(Vec3(73.0f, 50.0f, 0.0f)); walls[1026]->setPos(Vec3(74.0f, 50.0f, 0.0f));
walls[1027]->setPos(Vec3(75.0f, 50.0f, 0.0f)); walls[1028]->setPos(Vec3(76.0f, 50.0f, 0.0f));walls[1029]->setPos(Vec3(77.0f, 50.0f, 0.0f)); walls[1030]->setPos(Vec3(78.0f, 50.0f, 0.0f));
walls[1031]->setPos(Vec3(79.0f, 50.0f, 0.0f)); walls[1032]->setPos(Vec3(80.0f, 50.0f, 0.0f));walls[1033]->setPos(Vec3(81.0f, 50.0f, 0.0f)); walls[1034]->setPos(Vec3(82.0f, 50.0f, 0.0f));
walls[1035]->setPos(Vec3(83.0f, 50.0f, 0.0f)); walls[1036]->setPos(Vec3(84.0f, 50.0f, 0.0f));walls[1037]->setPos(Vec3(85.0f, 50.0f, 0.0f)); walls[1038]->setPos(Vec3(86.0f, 50.0f, 0.0f));
walls[1039]->setPos(Vec3(87.0f, 50.0f, 0.0f)); walls[1040]->setPos(Vec3(88.0f, 50.0f, 0.0f));walls[1041]->setPos(Vec3(89.0f, 50.0f, 0.0f)); walls[1042]->setPos(Vec3(90.0f, 50.0f, 0.0f));
walls[1043]->setPos(Vec3(91.0f, 50.0f, 0.0f)); walls[1044]->setPos(Vec3(92.0f, 50.0f, 0.0f));walls[1045]->setPos(Vec3(93.0f, 50.0f, 0.0f)); walls[1046]->setPos(Vec3(94.0f, 50.0f, 0.0f));
walls[1047]->setPos(Vec3(95.0f, 50.0f, 0.0f)); walls[1048]->setPos(Vec3(96.0f, 50.0f, 0.0f));walls[1049]->setPos(Vec3(97.0f, 50.0f, 0.0f)); walls[1050]->setPos(Vec3(98.0f, 50.0f, 0.0f));
walls[1051]->setPos(Vec3(99.0f, 50.0f, 0.0f)); walls[1052]->setPos(Vec3(100.0f, 50.0f, 0.0f));walls[1053]->setPos(Vec3(101.0f, 50.0f, 0.0f)); walls[1054]->setPos(Vec3(102.0f, 50.0f, 0.0f));
walls[1055]->setPos(Vec3(103.0f, 50.0f, 0.0f)); walls[1056]->setPos(Vec3(104.0f, 50.0f, 0.0f));walls[1057]->setPos(Vec3(105.0f, 50.0f, 0.0f)); walls[1058]->setPos(Vec3(106.0f, 50.0f, 0.0f));
walls[1059]->setPos(Vec3(107.0f, 50.0f, 0.0f)); walls[1060]->setPos(Vec3(108.0f, 50.0f, 0.0f));walls[1061]->setPos(Vec3(109.0f, 50.0f, 0.0f)); walls[1062]->setPos(Vec3(110.0f, 50.0f, 0.0f));
walls[1063]->setPos(Vec3(111.0f, 50.0f, 0.0f)); walls[1064]->setPos(Vec3(112.0f, 50.0f, 0.0f));walls[1065]->setPos(Vec3(113.0f, 50.0f, 0.0f)); walls[1066]->setPos(Vec3(114.0f, 50.0f, 0.0f));
walls[1067]->setPos(Vec3(115.0f, 50.0f, 0.0f));walls[1068]->setPos(Vec3(116.0f, 50.0f, 0.0f));walls[1069]->setPos(Vec3(117.0f, 50.0f, 0.0f)); walls[1070]->setPos(Vec3(118.0f, 50.0f, 0.0f));
walls[1071]->setPos(Vec3(119.0f, 50.0f, 0.0f)); walls[1072]->setPos(Vec3(120.0f, 50.0f, 0.0f));walls[1073]->setPos(Vec3(121.0f, 50.0f, 0.0f));walls[1074]->setPos(Vec3(122.0f, 50.0f, 0.0f));
walls[1075]->setPos(Vec3(123.0f, 50.0f, 0.0f));walls[1076]->setPos(Vec3(124.0f, 50.0f, 0.0f));walls[1077]->setPos(Vec3(125.0f, 50.0f, 0.0f));walls[1078]->setPos(Vec3(126.0f, 50.0f, 0.0f));
walls[1079]->setPos(Vec3(127.0f, 50.0f, 0.0f));walls[1080]->setPos(Vec3(128.0f, 50.0f, 0.0f));walls[1081]->setPos(Vec3(129.0f, 50.0f, 0.0f));walls[1082]->setPos(Vec3(130.0f, 50.0f, 0.0f));
walls[1083]->setPos(Vec3(131.0f, 50.0f, 0.0f));walls[1084]->setPos(Vec3(132.0f, 50.0f, 0.0f));walls[1085]->setPos(Vec3(133.0f, 50.0f, 0.0f));walls[1086]->setPos(Vec3(134.0f, 50.0f, 0.0f));
walls[1087]->setPos(Vec3(135.0f, 50.0f, 0.0f));walls[1088]->setPos(Vec3(136.0f, 50.0f, 0.0f));walls[1089]->setPos(Vec3(137.0f, 50.0f, 0.0f));walls[1090]->setPos(Vec3(138.0f, 50.0f, 0.0f));
walls[1091]->setPos(Vec3(139.0f, 50.0f, 0.0f));walls[1092]->setPos(Vec3(140.0f, 50.0f, 0.0f));walls[1093]->setPos(Vec3(141.0f, 50.0f, 0.0f));walls[1094]->setPos(Vec3(142.0f, 50.0f, 0.0f));
walls[1095]->setPos(Vec3(143.0f, 50.0f, 0.0f));walls[1096]->setPos(Vec3(144.0f, 50.0f, 0.0f));walls[1097]->setPos(Vec3(145.0f, 50.0f, 0.0f));walls[1098]->setPos(Vec3(146.0f, 50.0f, 0.0f));
walls[1099]->setPos(Vec3(147.0f, 50.0f, 0.0f));walls[1100]->setPos(Vec3(148.0f, 50.0f, 0.0f));walls[1101]->setPos(Vec3(149.0f, 50.0f, 0.0f));walls[1102]->setPos(Vec3(150.0f, 50.0f, 0.0f));
walls[1103]->setPos(Vec3(151.0f, 50.0f, 0.0f));walls[1104]->setPos(Vec3(152.0f, 50.0f, 0.0f));walls[1105]->setPos(Vec3(153.0f, 50.0f, 0.0f));	walls[1106]->setPos(Vec3(154.0f, 50.0f, 0.0f));
walls[1107]->setPos(Vec3(155.0f, 50.0f, 0.0f));walls[1108]->setPos(Vec3(156.0f, 50.0f, 0.0f));walls[1109]->setPos(Vec3(157.0f, 50.0f, 0.0f));walls[1110]->setPos(Vec3(158.0f, 50.0f, 0.0f));
walls[1111]->setPos(Vec3(159.0f, 50.0f, 0.0f));walls[1112]->setPos(Vec3(160.0f, 50.0f, 0.0f));walls[1113]->setPos(Vec3(161.0f, 50.0f, 0.0f));walls[1114]->setPos(Vec3(162.0f, 50.0f, 0.0f));
walls[1115]->setPos(Vec3(163.0f, 50.0f, 0.0f));walls[1116]->setPos(Vec3(164.0f, 50.0f, 0.0f));walls[1117]->setPos(Vec3(165.0f, 50.0f, 0.0f));walls[1118]->setPos(Vec3(166.0f, 50.0f, 0.0f));
walls[1119]->setPos(Vec3(167.0f, 50.0f, 0.0f));walls[1120]->setPos(Vec3(168.0f, 50.0f, 0.0f));walls[1121]->setPos(Vec3(169.0f, 50.0f, 0.0f));walls[1122]->setPos(Vec3(170.0f, 50.0f, 0.0f));
walls[1123]->setPos(Vec3(171.0f, 50.0f, 0.0f));walls[1124]->setPos(Vec3(172.0f, 50.0f, 0.0f));walls[1125]->setPos(Vec3(173.0f, 50.0f, 0.0f));walls[1126]->setPos(Vec3(174.0f, 50.0f, 0.0f));
walls[1127]->setPos(Vec3(175.0f, 50.0f, 0.0f));walls[1128]->setPos(Vec3(176.0f, 50.0f, 0.0f));walls[1129]->setPos(Vec3(177.0f, 50.0f, 0.0f));	walls[1130]->setPos(Vec3(178.0f, 50.0f, 0.0f));
walls[1131]->setPos(Vec3(179.0f, 50.0f, 0.0f)); walls[1132]->setPos(Vec3(180.0f, 50.0f, 0.0f));walls[1133]->setPos(Vec3(181.0f, 50.0f, 0.0f));	walls[1134]->setPos(Vec3(182.0f, 50.0f, 0.0f));
walls[1135]->setPos(Vec3(183.0f, 50.0f, 0.0f));walls[1136]->setPos(Vec3(184.0f, 50.0f, 0.0f));walls[1137]->setPos(Vec3(185.0f, 50.0f, 0.0f));walls[1138]->setPos(Vec3(186.0f, 50.0f, 0.0f));
walls[1139]->setPos(Vec3(187.0f, 50.0f, 0.0f)); walls[1140]->setPos(Vec3(188.0f, 50.0f, 0.0f));walls[1141]->setPos(Vec3(189.0f, 50.0f, 0.0f)); walls[1142]->setPos(Vec3(190.0f, 50.0f, 0.0f));
walls[1143]->setPos(Vec3(191.0f, 50.0f, 0.0f)); walls[1144]->setPos(Vec3(192.0f, 50.0f, 0.0f));walls[1145]->setPos(Vec3(193.0f, 50.0f, 0.0f)); walls[1146]->setPos(Vec3(194.0f, 50.0f, 0.0f));//5
walls[1147]->setPos(Vec3(195.0f, 50.0f, 0.0f)); walls[1148]->setPos(Vec3(196.0f, 50.0f, 0.0f));walls[1149]->setPos(Vec3(197.0f, 50.0f, 0.0f)); walls[1150]->setPos(Vec3(198.0f, 50.0f, 0.0f));//9
walls[1151]->setPos(Vec3(199.0f, 50.0f, 0.0f)); walls[1152]->setPos(Vec3(200.0f, 50.0f, 0.0f));walls[1153]->setPos(Vec3(201.0f, 50.0f, 0.0f)); walls[1154]->setPos(Vec3(202.0f, 50.0f, 0.0f));
walls[1155]->setPos(Vec3(203.0f, 50.0f, 0.0f));walls[1156]->setPos(Vec3(204.0f, 50.0f, 0.0f));walls[1157]->setPos(Vec3(205.0f, 50.0f, 0.0f)); walls[1158]->setPos(Vec3(206.0f, 50.0f, 0.0f));//7
walls[1159]->setPos(Vec3(207.0f, 50.0f, 0.0f)); walls[1160]->setPos(Vec3(208.0f, 50.0f, 0.0f));walls[1161]->setPos(Vec3(209.0f, 50.0f, 0.0f));walls[1162]->setPos(Vec3(210.0f, 50.0f, 0.0f));//1
walls[1163]->setPos(Vec3(211.0f, 50.0f, 0.0f));walls[1164]->setPos(Vec3(212.0f, 50.0f, 0.0f));walls[1165]->setPos(Vec3(213.0f, 50.0f, 0.0f));walls[1166]->setPos(Vec3(214.0f, 50.0f, 0.0f));//5
walls[1167]->setPos(Vec3(215.0f, 50.0f, 0.0f)); walls[1168]->setPos(Vec3(216.0f, 50.0f, 0.0f));walls[1169]->setPos(Vec3(217.0f, 50.0f, 0.0f)); walls[1170]->setPos(Vec3(218.0f, 50.0f, 0.0f));//9
walls[1171]->setPos(Vec3(219.0f, 50.0f, 0.0f));walls[1172]->setPos(Vec3(220.0f, 50.0f, 0.0f));walls[1173]->setPos(Vec3(221.0f, 50.0f, 0.0f)); walls[1174]->setPos(Vec3(222.0f, 50.0f, 0.0f));//3
walls[1175]->setPos(Vec3(223.0f, 50.0f, 0.0f)); walls[1176]->setPos(Vec3(224.0f, 50.0f, 0.0f));walls[1177]->setPos(Vec3(225.0f, 50.0f, 0.0f)); walls[1178]->setPos(Vec3(226.0f, 50.0f, 0.0f));//7
walls[1179]->setPos(Vec3(227.0f, 50.0f, 0.0f)); walls[1180]->setPos(Vec3(228.0f, 50.0f, 0.0f));walls[1181]->setPos(Vec3(229.0f, 50.0f, 0.0f)); walls[1183]->setPos(Vec3(230.0f, 50.0f, 0.0f));//1
walls[1184]->setPos(Vec3(231.0f, 50.0f, 0.0f)); walls[1185]->setPos(Vec3(232.0f, 50.0f, 0.0f));walls[1186]->setPos(Vec3(233.0f, 50.0f, 0.0f)); walls[1187]->setPos(Vec3(234.0f, 50.0f, 0.0f));//5
walls[1188]->setPos(Vec3(235.0f, 50.0f, 0.0f)); walls[1189]->setPos(Vec3(236.0f, 50.0f, 0.0f));walls[1190]->setPos(Vec3(237.0f, 50.0f, 0.0f)); walls[1191]->setPos(Vec3(238.0f, 50.0f, 0.0f));//9
walls[1192]->setPos(Vec3(239.0f, 50.0f, 0.0f)); walls[1193]->setPos(Vec3(240.0f, 50.0f, 0.0f));walls[1194]->setPos(Vec3(241.0f, 50.0f, 0.0f)); walls[1195]->setPos(Vec3(242.0f, 50.0f, 0.0f));//3
walls[1196]->setPos(Vec3(243.0f, 50.0f, 0.0f)); walls[1197]->setPos(Vec3(244.0f, 50.0f, 0.0f));walls[1198]->setPos(Vec3(245.0f, 50.0f, 0.0f));	walls[1199]->setPos(Vec3(246.0f, 50.0f, 0.0f));//7
walls[1200]->setPos(Vec3(247.0f, 50.0f, 0.0f));	walls[1201]->setPos(Vec3(248.0f, 50.0f, 0.0f));walls[1202]->setPos(Vec3(249.0f, 50.0f, 0.0f));//10
#pragma endregion
		break;
	default:
		break;
	}
}

void Level::setWallTextures(SDL_Texture* texturePtr){
	for (int i = 0; i < wallNum; i++)
		walls[i]->setTexture(texturePtr);
}