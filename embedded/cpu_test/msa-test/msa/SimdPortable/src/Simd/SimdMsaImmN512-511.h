#ifndef _SIMDMSAIMMN512_511_H_
#define _SIMDMSAIMMN512_511_H_

#define TYPE_IMM_N512_511_FUNC(Template,Func,CODE)						\
	Template(Func,-16,CODE);	Template(Func,-15,CODE);	Template(Func,-14,CODE);	Template(Func,-13,CODE); \
	Template(Func,-12,CODE);	Template(Func,-11,CODE);	Template(Func,-10,CODE);	Template(Func,-9,CODE); \
	Template(Func,-8,CODE);	Template(Func,-7,CODE);	Template(Func,-6,CODE);	Template(Func,-5,CODE); \
	Template(Func,-4,CODE);	Template(Func,-3,CODE);	Template(Func,-2,CODE);	Template(Func,-1,CODE); \
	Template(Func,0,CODE);	Template(Func,1,CODE);	Template(Func,2,CODE);	Template(Func,3,CODE); \
	Template(Func,4,CODE);	Template(Func,5,CODE);	Template(Func,6,CODE);	Template(Func,7,CODE); \
	Template(Func,8,CODE);	Template(Func,9,CODE);	Template(Func,10,CODE);	Template(Func,11,CODE); \
	Template(Func,12,CODE);	Template(Func,13,CODE);	Template(Func,14,CODE);	Template(Func,15,CODE); \
	Template(Func,16,CODE);	Template(Func,17,CODE);	Template(Func,18,CODE);	Template(Func,19,CODE); \


#if 0
		Template(Func,-512,CODE);	Template(Func,-511,CODE);	Template(Func,-510,CODE);	Template(Func,-509,CODE); \
		Template(Func,-508,CODE);	Template(Func,-507,CODE);	Template(Func,-506,CODE);	Template(Func,-505,CODE); \
		Template(Func,-504,CODE);	Template(Func,-503,CODE);	Template(Func,-502,CODE);	Template(Func,-501,CODE); \
		Template(Func,-500,CODE);	Template(Func,-499,CODE);	Template(Func,-498,CODE);	Template(Func,-497,CODE); \
		Template(Func,-496,CODE);	Template(Func,-495,CODE);	Template(Func,-494,CODE);	Template(Func,-493,CODE); \
		Template(Func,-492,CODE);	Template(Func,-491,CODE);	Template(Func,-490,CODE);	Template(Func,-489,CODE); \
		Template(Func,-488,CODE);	Template(Func,-487,CODE);	Template(Func,-486,CODE);	Template(Func,-485,CODE); \
		Template(Func,-484,CODE);	Template(Func,-483,CODE);	Template(Func,-482,CODE);	Template(Func,-481,CODE); \
		Template(Func,-480,CODE);	Template(Func,-479,CODE);	Template(Func,-478,CODE);	Template(Func,-477,CODE); \
		Template(Func,-476,CODE);	Template(Func,-475,CODE);	Template(Func,-474,CODE);	Template(Func,-473,CODE); \
		Template(Func,-472,CODE);	Template(Func,-471,CODE);	Template(Func,-470,CODE);	Template(Func,-469,CODE); \
		Template(Func,-468,CODE);	Template(Func,-467,CODE);	Template(Func,-466,CODE);	Template(Func,-465,CODE); \
		Template(Func,-464,CODE);	Template(Func,-463,CODE);	Template(Func,-462,CODE);	Template(Func,-461,CODE); \
		Template(Func,-460,CODE);	Template(Func,-459,CODE);	Template(Func,-458,CODE);	Template(Func,-457,CODE); \
		Template(Func,-456,CODE);	Template(Func,-455,CODE);	Template(Func,-454,CODE);	Template(Func,-453,CODE); \
		Template(Func,-452,CODE);	Template(Func,-451,CODE);	Template(Func,-450,CODE);	Template(Func,-449,CODE); \
		Template(Func,-448,CODE);	Template(Func,-447,CODE);	Template(Func,-446,CODE);	Template(Func,-445,CODE); \
		Template(Func,-444,CODE);	Template(Func,-443,CODE);	Template(Func,-442,CODE);	Template(Func,-441,CODE); \
		Template(Func,-440,CODE);	Template(Func,-439,CODE);	Template(Func,-438,CODE);	Template(Func,-437,CODE); \
		Template(Func,-436,CODE);	Template(Func,-435,CODE);	Template(Func,-434,CODE);	Template(Func,-433,CODE); \
		Template(Func,-432,CODE);	Template(Func,-431,CODE);	Template(Func,-430,CODE);	Template(Func,-429,CODE); \
		Template(Func,-428,CODE);	Template(Func,-427,CODE);	Template(Func,-426,CODE);	Template(Func,-425,CODE); \
		Template(Func,-424,CODE);	Template(Func,-423,CODE);	Template(Func,-422,CODE);	Template(Func,-421,CODE); \
		Template(Func,-420,CODE);	Template(Func,-419,CODE);	Template(Func,-418,CODE);	Template(Func,-417,CODE); \
		Template(Func,-416,CODE);	Template(Func,-415,CODE);	Template(Func,-414,CODE);	Template(Func,-413,CODE); \
		Template(Func,-412,CODE);	Template(Func,-411,CODE);	Template(Func,-410,CODE);	Template(Func,-409,CODE); \
		Template(Func,-408,CODE);	Template(Func,-407,CODE);	Template(Func,-406,CODE);	Template(Func,-405,CODE); \
		Template(Func,-404,CODE);	Template(Func,-403,CODE);	Template(Func,-402,CODE);	Template(Func,-401,CODE); \
		Template(Func,-400,CODE);	Template(Func,-399,CODE);	Template(Func,-398,CODE);	Template(Func,-397,CODE); \
		Template(Func,-396,CODE);	Template(Func,-395,CODE);	Template(Func,-394,CODE);	Template(Func,-393,CODE); \
		Template(Func,-392,CODE);	Template(Func,-391,CODE);	Template(Func,-390,CODE);	Template(Func,-389,CODE); \
		Template(Func,-388,CODE);	Template(Func,-387,CODE);	Template(Func,-386,CODE);	Template(Func,-385,CODE); \
		Template(Func,-384,CODE);	Template(Func,-383,CODE);	Template(Func,-382,CODE);	Template(Func,-381,CODE); \
		Template(Func,-380,CODE);	Template(Func,-379,CODE);	Template(Func,-378,CODE);	Template(Func,-377,CODE); \
		Template(Func,-376,CODE);	Template(Func,-375,CODE);	Template(Func,-374,CODE);	Template(Func,-373,CODE); \
		Template(Func,-372,CODE);	Template(Func,-371,CODE);	Template(Func,-370,CODE);	Template(Func,-369,CODE); \
		Template(Func,-368,CODE);	Template(Func,-367,CODE);	Template(Func,-366,CODE);	Template(Func,-365,CODE); \
		Template(Func,-364,CODE);	Template(Func,-363,CODE);	Template(Func,-362,CODE);	Template(Func,-361,CODE); \
		Template(Func,-360,CODE);	Template(Func,-359,CODE);	Template(Func,-358,CODE);	Template(Func,-357,CODE); \
		Template(Func,-356,CODE);	Template(Func,-355,CODE);	Template(Func,-354,CODE);	Template(Func,-353,CODE); \
		Template(Func,-352,CODE);	Template(Func,-351,CODE);	Template(Func,-350,CODE);	Template(Func,-349,CODE); \
		Template(Func,-348,CODE);	Template(Func,-347,CODE);	Template(Func,-346,CODE);	Template(Func,-345,CODE); \
		Template(Func,-344,CODE);	Template(Func,-343,CODE);	Template(Func,-342,CODE);	Template(Func,-341,CODE); \
		Template(Func,-340,CODE);	Template(Func,-339,CODE);	Template(Func,-338,CODE);	Template(Func,-337,CODE); \
		Template(Func,-336,CODE);	Template(Func,-335,CODE);	Template(Func,-334,CODE);	Template(Func,-333,CODE); \
		Template(Func,-332,CODE);	Template(Func,-331,CODE);	Template(Func,-330,CODE);	Template(Func,-329,CODE); \
		Template(Func,-328,CODE);	Template(Func,-327,CODE);	Template(Func,-326,CODE);	Template(Func,-325,CODE); \
		Template(Func,-324,CODE);	Template(Func,-323,CODE);	Template(Func,-322,CODE);	Template(Func,-321,CODE); \
		Template(Func,-320,CODE);	Template(Func,-319,CODE);	Template(Func,-318,CODE);	Template(Func,-317,CODE); \
		Template(Func,-316,CODE);	Template(Func,-315,CODE);	Template(Func,-314,CODE);	Template(Func,-313,CODE); \
		Template(Func,-312,CODE);	Template(Func,-311,CODE);	Template(Func,-310,CODE);	Template(Func,-309,CODE); \
		Template(Func,-308,CODE);	Template(Func,-307,CODE);	Template(Func,-306,CODE);	Template(Func,-305,CODE); \
		Template(Func,-304,CODE);	Template(Func,-303,CODE);	Template(Func,-302,CODE);	Template(Func,-301,CODE); \
		Template(Func,-300,CODE);	Template(Func,-299,CODE);	Template(Func,-298,CODE);	Template(Func,-297,CODE); \
		Template(Func,-296,CODE);	Template(Func,-295,CODE);	Template(Func,-294,CODE);	Template(Func,-293,CODE); \
		Template(Func,-292,CODE);	Template(Func,-291,CODE);	Template(Func,-290,CODE);	Template(Func,-289,CODE); \
		Template(Func,-288,CODE);	Template(Func,-287,CODE);	Template(Func,-286,CODE);	Template(Func,-285,CODE); \
		Template(Func,-284,CODE);	Template(Func,-283,CODE);	Template(Func,-282,CODE);	Template(Func,-281,CODE); \
		Template(Func,-280,CODE);	Template(Func,-279,CODE);	Template(Func,-278,CODE);	Template(Func,-277,CODE); \
		Template(Func,-276,CODE);	Template(Func,-275,CODE);	Template(Func,-274,CODE);	Template(Func,-273,CODE); \
		Template(Func,-272,CODE);	Template(Func,-271,CODE);	Template(Func,-270,CODE);	Template(Func,-269,CODE); \
		Template(Func,-268,CODE);	Template(Func,-267,CODE);	Template(Func,-266,CODE);	Template(Func,-265,CODE); \
		Template(Func,-264,CODE);	Template(Func,-263,CODE);	Template(Func,-262,CODE);	Template(Func,-261,CODE); \
		Template(Func,-260,CODE);	Template(Func,-259,CODE);	Template(Func,-258,CODE);	Template(Func,-257,CODE); \
		Template(Func,-256,CODE);	Template(Func,-255,CODE);	Template(Func,-254,CODE);	Template(Func,-253,CODE); \
		Template(Func,-252,CODE);	Template(Func,-251,CODE);	Template(Func,-250,CODE);	Template(Func,-249,CODE); \
		Template(Func,-248,CODE);	Template(Func,-247,CODE);	Template(Func,-246,CODE);	Template(Func,-245,CODE); \
		Template(Func,-244,CODE);	Template(Func,-243,CODE);	Template(Func,-242,CODE);	Template(Func,-241,CODE); \
		Template(Func,-240,CODE);	Template(Func,-239,CODE);	Template(Func,-238,CODE);	Template(Func,-237,CODE); \
		Template(Func,-236,CODE);	Template(Func,-235,CODE);	Template(Func,-234,CODE);	Template(Func,-233,CODE); \
		Template(Func,-232,CODE);	Template(Func,-231,CODE);	Template(Func,-230,CODE);	Template(Func,-229,CODE); \
		Template(Func,-228,CODE);	Template(Func,-227,CODE);	Template(Func,-226,CODE);	Template(Func,-225,CODE); \
		Template(Func,-224,CODE);	Template(Func,-223,CODE);	Template(Func,-222,CODE);	Template(Func,-221,CODE); \
		Template(Func,-220,CODE);	Template(Func,-219,CODE);	Template(Func,-218,CODE);	Template(Func,-217,CODE); \
		Template(Func,-216,CODE);	Template(Func,-215,CODE);	Template(Func,-214,CODE);	Template(Func,-213,CODE); \
		Template(Func,-212,CODE);	Template(Func,-211,CODE);	Template(Func,-210,CODE);	Template(Func,-209,CODE); \
		Template(Func,-208,CODE);	Template(Func,-207,CODE);	Template(Func,-206,CODE);	Template(Func,-205,CODE); \
		Template(Func,-204,CODE);	Template(Func,-203,CODE);	Template(Func,-202,CODE);	Template(Func,-201,CODE); \
		Template(Func,-200,CODE);	Template(Func,-199,CODE);	Template(Func,-198,CODE);	Template(Func,-197,CODE); \
		Template(Func,-196,CODE);	Template(Func,-195,CODE);	Template(Func,-194,CODE);	Template(Func,-193,CODE); \
		Template(Func,-192,CODE);	Template(Func,-191,CODE);	Template(Func,-190,CODE);	Template(Func,-189,CODE); \
		Template(Func,-188,CODE);	Template(Func,-187,CODE);	Template(Func,-186,CODE);	Template(Func,-185,CODE); \
		Template(Func,-184,CODE);	Template(Func,-183,CODE);	Template(Func,-182,CODE);	Template(Func,-181,CODE); \
		Template(Func,-180,CODE);	Template(Func,-179,CODE);	Template(Func,-178,CODE);	Template(Func,-177,CODE); \
		Template(Func,-176,CODE);	Template(Func,-175,CODE);	Template(Func,-174,CODE);	Template(Func,-173,CODE); \
		Template(Func,-172,CODE);	Template(Func,-171,CODE);	Template(Func,-170,CODE);	Template(Func,-169,CODE); \
		Template(Func,-168,CODE);	Template(Func,-167,CODE);	Template(Func,-166,CODE);	Template(Func,-165,CODE); \
		Template(Func,-164,CODE);	Template(Func,-163,CODE);	Template(Func,-162,CODE);	Template(Func,-161,CODE); \
		Template(Func,-160,CODE);	Template(Func,-159,CODE);	Template(Func,-158,CODE);	Template(Func,-157,CODE); \
		Template(Func,-156,CODE);	Template(Func,-155,CODE);	Template(Func,-154,CODE);	Template(Func,-153,CODE); \
		Template(Func,-152,CODE);	Template(Func,-151,CODE);	Template(Func,-150,CODE);	Template(Func,-149,CODE); \
		Template(Func,-148,CODE);	Template(Func,-147,CODE);	Template(Func,-146,CODE);	Template(Func,-145,CODE); \
		Template(Func,-144,CODE);	Template(Func,-143,CODE);	Template(Func,-142,CODE);	Template(Func,-141,CODE); \
		Template(Func,-140,CODE);	Template(Func,-139,CODE);	Template(Func,-138,CODE);	Template(Func,-137,CODE); \
		Template(Func,-136,CODE);	Template(Func,-135,CODE);	Template(Func,-134,CODE);	Template(Func,-133,CODE); \
		Template(Func,-132,CODE);	Template(Func,-131,CODE);	Template(Func,-130,CODE);	Template(Func,-129,CODE); \
		Template(Func,-128,CODE);	Template(Func,-127,CODE);	Template(Func,-126,CODE);	Template(Func,-125,CODE); \
		Template(Func,-124,CODE);	Template(Func,-123,CODE);	Template(Func,-122,CODE);	Template(Func,-121,CODE); \
		Template(Func,-120,CODE);	Template(Func,-119,CODE);	Template(Func,-118,CODE);	Template(Func,-117,CODE); \
		Template(Func,-116,CODE);	Template(Func,-115,CODE);	Template(Func,-114,CODE);	Template(Func,-113,CODE); \
		Template(Func,-112,CODE);	Template(Func,-111,CODE);	Template(Func,-110,CODE);	Template(Func,-109,CODE); \
		Template(Func,-108,CODE);	Template(Func,-107,CODE);	Template(Func,-106,CODE);	Template(Func,-105,CODE); \
		Template(Func,-104,CODE);	Template(Func,-103,CODE);	Template(Func,-102,CODE);	Template(Func,-101,CODE); \
		Template(Func,-100,CODE);	Template(Func,-99,CODE);	Template(Func,-98,CODE);	Template(Func,-97,CODE);	\
		Template(Func,-96,CODE);	Template(Func,-95,CODE);	Template(Func,-94,CODE);	Template(Func,-93,CODE);	\
		Template(Func,-92,CODE);	Template(Func,-91,CODE);	Template(Func,-90,CODE);	Template(Func,-89,CODE);	\
		Template(Func,-88,CODE);	Template(Func,-87,CODE);	Template(Func,-86,CODE);	Template(Func,-85,CODE);	\
		Template(Func,-84,CODE);	Template(Func,-83,CODE);	Template(Func,-82,CODE);	Template(Func,-81,CODE);	\
		Template(Func,-80,CODE);	Template(Func,-79,CODE);	Template(Func,-78,CODE);	Template(Func,-77,CODE);	\
		Template(Func,-76,CODE);	Template(Func,-75,CODE);	Template(Func,-74,CODE);	Template(Func,-73,CODE);	\
		Template(Func,-72,CODE);	Template(Func,-71,CODE);	Template(Func,-70,CODE);	Template(Func,-69,CODE);	\
		Template(Func,-68,CODE);	Template(Func,-67,CODE);	Template(Func,-66,CODE);	Template(Func,-65,CODE);	\
		Template(Func,-64,CODE);	Template(Func,-63,CODE);	Template(Func,-62,CODE);	Template(Func,-61,CODE);	\
		Template(Func,-60,CODE);	Template(Func,-59,CODE);	Template(Func,-58,CODE);	Template(Func,-57,CODE);	\
		Template(Func,-56,CODE);	Template(Func,-55,CODE);	Template(Func,-54,CODE);	Template(Func,-53,CODE);	\
		Template(Func,-52,CODE);	Template(Func,-51,CODE);	Template(Func,-50,CODE);	Template(Func,-49,CODE);	\
		Template(Func,-48,CODE);	Template(Func,-47,CODE);	Template(Func,-46,CODE);	Template(Func,-45,CODE);	\
		Template(Func,-44,CODE);	Template(Func,-43,CODE);	Template(Func,-42,CODE);	Template(Func,-41,CODE);	\
		Template(Func,-40,CODE);	Template(Func,-39,CODE);	Template(Func,-38,CODE);	Template(Func,-37,CODE);	\
		Template(Func,-36,CODE);	Template(Func,-35,CODE);	Template(Func,-34,CODE);	Template(Func,-33,CODE);	\
		Template(Func,-32,CODE);	Template(Func,-31,CODE);	Template(Func,-30,CODE);	Template(Func,-29,CODE);	\
		Template(Func,-28,CODE);	Template(Func,-27,CODE);	Template(Func,-26,CODE);	Template(Func,-25,CODE);	\
		Template(Func,-24,CODE);	Template(Func,-23,CODE);	Template(Func,-22,CODE);	Template(Func,-21,CODE);	\
		Template(Func,-20,CODE);	Template(Func,-19,CODE);	Template(Func,-18,CODE);	Template(Func,-17,CODE);	\
		Template(Func,-16,CODE);	Template(Func,-15,CODE);	Template(Func,-14,CODE);	Template(Func,-13,CODE);	\
		Template(Func,-12,CODE);	Template(Func,-11,CODE);	Template(Func,-10,CODE);	Template(Func,-9,CODE); \
		Template(Func,-8,CODE);	Template(Func,-7,CODE);	Template(Func,-6,CODE);	Template(Func,-5,CODE); \
		Template(Func,-4,CODE);	Template(Func,-3,CODE);	Template(Func,-2,CODE);	Template(Func,-1,CODE); \
		Template(Func,0,CODE);	Template(Func,1,CODE);	Template(Func,2,CODE);	Template(Func,3,CODE); \
		Template(Func,4,CODE);	Template(Func,5,CODE);	Template(Func,6,CODE);	Template(Func,7,CODE); \
		Template(Func,8,CODE);	Template(Func,9,CODE);	Template(Func,10,CODE);	Template(Func,11,CODE); \
		Template(Func,12,CODE);	Template(Func,13,CODE);	Template(Func,14,CODE);	Template(Func,15,CODE); \
		Template(Func,16,CODE);	Template(Func,17,CODE);	Template(Func,18,CODE);	Template(Func,19,CODE); \
		Template(Func,20,CODE);	Template(Func,21,CODE);	Template(Func,22,CODE);	Template(Func,23,CODE); \
		Template(Func,24,CODE);	Template(Func,25,CODE);	Template(Func,26,CODE);	Template(Func,27,CODE); \
		Template(Func,28,CODE);	Template(Func,29,CODE);	Template(Func,30,CODE);	Template(Func,31,CODE); \
		Template(Func,32,CODE);	Template(Func,33,CODE);	Template(Func,34,CODE);	Template(Func,35,CODE); \
		Template(Func,36,CODE);	Template(Func,37,CODE);	Template(Func,38,CODE);	Template(Func,39,CODE); \
		Template(Func,40,CODE);	Template(Func,41,CODE);	Template(Func,42,CODE);	Template(Func,43,CODE); \
		Template(Func,44,CODE);	Template(Func,45,CODE);	Template(Func,46,CODE);	Template(Func,47,CODE); \
		Template(Func,48,CODE);	Template(Func,49,CODE);	Template(Func,50,CODE);	Template(Func,51,CODE); \
		Template(Func,52,CODE);	Template(Func,53,CODE);	Template(Func,54,CODE);	Template(Func,55,CODE); \
		Template(Func,56,CODE);	Template(Func,57,CODE);	Template(Func,58,CODE);	Template(Func,59,CODE); \
		Template(Func,60,CODE);	Template(Func,61,CODE);	Template(Func,62,CODE);	Template(Func,63,CODE); \
		Template(Func,64,CODE);	Template(Func,65,CODE);	Template(Func,66,CODE);	Template(Func,67,CODE); \
		Template(Func,68,CODE);	Template(Func,69,CODE);	Template(Func,70,CODE);	Template(Func,71,CODE); \
		Template(Func,72,CODE);	Template(Func,73,CODE);	Template(Func,74,CODE);	Template(Func,75,CODE); \
		Template(Func,76,CODE);	Template(Func,77,CODE);	Template(Func,78,CODE);	Template(Func,79,CODE); \
		Template(Func,80,CODE);	Template(Func,81,CODE);	Template(Func,82,CODE);	Template(Func,83,CODE); \
		Template(Func,84,CODE);	Template(Func,85,CODE);	Template(Func,86,CODE);	Template(Func,87,CODE); \
		Template(Func,88,CODE);	Template(Func,89,CODE);	Template(Func,90,CODE);	Template(Func,91,CODE); \
		Template(Func,92,CODE);	Template(Func,93,CODE);	Template(Func,94,CODE);	Template(Func,95,CODE); \
		Template(Func,96,CODE);	Template(Func,97,CODE);	Template(Func,98,CODE);	Template(Func,99,CODE); \
		Template(Func,100,CODE);	Template(Func,101,CODE);	Template(Func,102,CODE);	Template(Func,103,CODE);	\
		Template(Func,104,CODE);	Template(Func,105,CODE);	Template(Func,106,CODE);	Template(Func,107,CODE);	\
		Template(Func,108,CODE);	Template(Func,109,CODE);	Template(Func,110,CODE);	Template(Func,111,CODE);	\
		Template(Func,112,CODE);	Template(Func,113,CODE);	Template(Func,114,CODE);	Template(Func,115,CODE);	\
		Template(Func,116,CODE);	Template(Func,117,CODE);	Template(Func,118,CODE);	Template(Func,119,CODE);	\
		Template(Func,120,CODE);	Template(Func,121,CODE);	Template(Func,122,CODE);	Template(Func,123,CODE);	\
		Template(Func,124,CODE);	Template(Func,125,CODE);	Template(Func,126,CODE);	Template(Func,127,CODE);	\
		Template(Func,128,CODE);	Template(Func,129,CODE);	Template(Func,130,CODE);	Template(Func,131,CODE);	\
		Template(Func,132,CODE);	Template(Func,133,CODE);	Template(Func,134,CODE);	Template(Func,135,CODE);	\
		Template(Func,136,CODE);	Template(Func,137,CODE);	Template(Func,138,CODE);	Template(Func,139,CODE);	\
		Template(Func,140,CODE);	Template(Func,141,CODE);	Template(Func,142,CODE);	Template(Func,143,CODE);	\
		Template(Func,144,CODE);	Template(Func,145,CODE);	Template(Func,146,CODE);	Template(Func,147,CODE);	\
		Template(Func,148,CODE);	Template(Func,149,CODE);	Template(Func,150,CODE);	Template(Func,151,CODE);	\
		Template(Func,152,CODE);	Template(Func,153,CODE);	Template(Func,154,CODE);	Template(Func,155,CODE);	\
		Template(Func,156,CODE);	Template(Func,157,CODE);	Template(Func,158,CODE);	Template(Func,159,CODE);	\
		Template(Func,160,CODE);	Template(Func,161,CODE);	Template(Func,162,CODE);	Template(Func,163,CODE);	\
		Template(Func,164,CODE);	Template(Func,165,CODE);	Template(Func,166,CODE);	Template(Func,167,CODE);	\
		Template(Func,168,CODE);	Template(Func,169,CODE);	Template(Func,170,CODE);	Template(Func,171,CODE);	\
		Template(Func,172,CODE);	Template(Func,173,CODE);	Template(Func,174,CODE);	Template(Func,175,CODE);	\
		Template(Func,176,CODE);	Template(Func,177,CODE);	Template(Func,178,CODE);	Template(Func,179,CODE);	\
		Template(Func,180,CODE);	Template(Func,181,CODE);	Template(Func,182,CODE);	Template(Func,183,CODE);	\
		Template(Func,184,CODE);	Template(Func,185,CODE);	Template(Func,186,CODE);	Template(Func,187,CODE);	\
		Template(Func,188,CODE);	Template(Func,189,CODE);	Template(Func,190,CODE);	Template(Func,191,CODE);	\
		Template(Func,192,CODE);	Template(Func,193,CODE);	Template(Func,194,CODE);	Template(Func,195,CODE);	\
		Template(Func,196,CODE);	Template(Func,197,CODE);	Template(Func,198,CODE);	Template(Func,199,CODE);	\
		Template(Func,200,CODE);	Template(Func,201,CODE);	Template(Func,202,CODE);	Template(Func,203,CODE);	\
		Template(Func,204,CODE);	Template(Func,205,CODE);	Template(Func,206,CODE);	Template(Func,207,CODE);	\
		Template(Func,208,CODE);	Template(Func,209,CODE);	Template(Func,210,CODE);	Template(Func,211,CODE);	\
		Template(Func,212,CODE);	Template(Func,213,CODE);	Template(Func,214,CODE);	Template(Func,215,CODE);	\
		Template(Func,216,CODE);	Template(Func,217,CODE);	Template(Func,218,CODE);	Template(Func,219,CODE);	\
		Template(Func,220,CODE);	Template(Func,221,CODE);	Template(Func,222,CODE);	Template(Func,223,CODE);	\
		Template(Func,224,CODE);	Template(Func,225,CODE);	Template(Func,226,CODE);	Template(Func,227,CODE);	\
		Template(Func,228,CODE);	Template(Func,229,CODE);	Template(Func,230,CODE);	Template(Func,231,CODE);	\
		Template(Func,232,CODE);	Template(Func,233,CODE);	Template(Func,234,CODE);	Template(Func,235,CODE);	\
		Template(Func,236,CODE);	Template(Func,237,CODE);	Template(Func,238,CODE);	Template(Func,239,CODE);	\
		Template(Func,240,CODE);	Template(Func,241,CODE);	Template(Func,242,CODE);	Template(Func,243,CODE);	\
		Template(Func,244,CODE);	Template(Func,245,CODE);	Template(Func,246,CODE);	Template(Func,247,CODE);	\
		Template(Func,248,CODE);	Template(Func,249,CODE);	Template(Func,250,CODE);	Template(Func,251,CODE);	\
		Template(Func,252,CODE);	Template(Func,253,CODE);	Template(Func,254,CODE);	Template(Func,255,CODE);	\
		Template(Func,256,CODE);	Template(Func,257,CODE);	Template(Func,258,CODE);	Template(Func,259,CODE);	\
		Template(Func,260,CODE);	Template(Func,261,CODE);	Template(Func,262,CODE);	Template(Func,263,CODE);	\
		Template(Func,264,CODE);	Template(Func,265,CODE);	Template(Func,266,CODE);	Template(Func,267,CODE);	\
		Template(Func,268,CODE);	Template(Func,269,CODE);	Template(Func,270,CODE);	Template(Func,271,CODE);	\
		Template(Func,272,CODE);	Template(Func,273,CODE);	Template(Func,274,CODE);	Template(Func,275,CODE);	\
		Template(Func,276,CODE);	Template(Func,277,CODE);	Template(Func,278,CODE);	Template(Func,279,CODE);	\
		Template(Func,280,CODE);	Template(Func,281,CODE);	Template(Func,282,CODE);	Template(Func,283,CODE);	\
		Template(Func,284,CODE);	Template(Func,285,CODE);	Template(Func,286,CODE);	Template(Func,287,CODE);	\
		Template(Func,288,CODE);	Template(Func,289,CODE);	Template(Func,290,CODE);	Template(Func,291,CODE);	\
		Template(Func,292,CODE);	Template(Func,293,CODE);	Template(Func,294,CODE);	Template(Func,295,CODE);	\
		Template(Func,296,CODE);	Template(Func,297,CODE);	Template(Func,298,CODE);	Template(Func,299,CODE);	\
		Template(Func,300,CODE);	Template(Func,301,CODE);	Template(Func,302,CODE);	Template(Func,303,CODE);	\
		Template(Func,304,CODE);	Template(Func,305,CODE);	Template(Func,306,CODE);	Template(Func,307,CODE);	\
		Template(Func,308,CODE);	Template(Func,309,CODE);	Template(Func,310,CODE);	Template(Func,311,CODE);	\
		Template(Func,312,CODE);	Template(Func,313,CODE);	Template(Func,314,CODE);	Template(Func,315,CODE);	\
		Template(Func,316,CODE);	Template(Func,317,CODE);	Template(Func,318,CODE);	Template(Func,319,CODE);	\
		Template(Func,320,CODE);	Template(Func,321,CODE);	Template(Func,322,CODE);	Template(Func,323,CODE);	\
		Template(Func,324,CODE);	Template(Func,325,CODE);	Template(Func,326,CODE);	Template(Func,327,CODE);	\
		Template(Func,328,CODE);	Template(Func,329,CODE);	Template(Func,330,CODE);	Template(Func,331,CODE);	\
		Template(Func,332,CODE);	Template(Func,333,CODE);	Template(Func,334,CODE);	Template(Func,335,CODE);	\
		Template(Func,336,CODE);	Template(Func,337,CODE);	Template(Func,338,CODE);	Template(Func,339,CODE);	\
		Template(Func,340,CODE);	Template(Func,341,CODE);	Template(Func,342,CODE);	Template(Func,343,CODE);	\
		Template(Func,344,CODE);	Template(Func,345,CODE);	Template(Func,346,CODE);	Template(Func,347,CODE);	\
		Template(Func,348,CODE);	Template(Func,349,CODE);	Template(Func,350,CODE);	Template(Func,351,CODE);	\
		Template(Func,352,CODE);	Template(Func,353,CODE);	Template(Func,354,CODE);	Template(Func,355,CODE);	\
		Template(Func,356,CODE);	Template(Func,357,CODE);	Template(Func,358,CODE);	Template(Func,359,CODE);	\
		Template(Func,360,CODE);	Template(Func,361,CODE);	Template(Func,362,CODE);	Template(Func,363,CODE);	\
		Template(Func,364,CODE);	Template(Func,365,CODE);	Template(Func,366,CODE);	Template(Func,367,CODE);	\
		Template(Func,368,CODE);	Template(Func,369,CODE);	Template(Func,370,CODE);	Template(Func,371,CODE);	\
		Template(Func,372,CODE);	Template(Func,373,CODE);	Template(Func,374,CODE);	Template(Func,375,CODE);	\
		Template(Func,376,CODE);	Template(Func,377,CODE);	Template(Func,378,CODE);	Template(Func,379,CODE);	\
		Template(Func,380,CODE);	Template(Func,381,CODE);	Template(Func,382,CODE);	Template(Func,383,CODE);	\
		Template(Func,384,CODE);	Template(Func,385,CODE);	Template(Func,386,CODE);	Template(Func,387,CODE);	\
		Template(Func,388,CODE);	Template(Func,389,CODE);	Template(Func,390,CODE);	Template(Func,391,CODE);	\
		Template(Func,392,CODE);	Template(Func,393,CODE);	Template(Func,394,CODE);	Template(Func,395,CODE);	\
		Template(Func,396,CODE);	Template(Func,397,CODE);	Template(Func,398,CODE);	Template(Func,399,CODE);	\
		Template(Func,400,CODE);	Template(Func,401,CODE);	Template(Func,402,CODE);	Template(Func,403,CODE);	\
		Template(Func,404,CODE);	Template(Func,405,CODE);	Template(Func,406,CODE);	Template(Func,407,CODE);	\
		Template(Func,408,CODE);	Template(Func,409,CODE);	Template(Func,410,CODE);	Template(Func,411,CODE);	\
		Template(Func,412,CODE);	Template(Func,413,CODE);	Template(Func,414,CODE);	Template(Func,415,CODE);	\
		Template(Func,416,CODE);	Template(Func,417,CODE);	Template(Func,418,CODE);	Template(Func,419,CODE);	\
		Template(Func,420,CODE);	Template(Func,421,CODE);	Template(Func,422,CODE);	Template(Func,423,CODE);	\
		Template(Func,424,CODE);	Template(Func,425,CODE);	Template(Func,426,CODE);	Template(Func,427,CODE);	\
		Template(Func,428,CODE);	Template(Func,429,CODE);	Template(Func,430,CODE);	Template(Func,431,CODE);	\
		Template(Func,432,CODE);	Template(Func,433,CODE);	Template(Func,434,CODE);	Template(Func,435,CODE);	\
		Template(Func,436,CODE);	Template(Func,437,CODE);	Template(Func,438,CODE);	Template(Func,439,CODE);	\
		Template(Func,440,CODE);	Template(Func,441,CODE);	Template(Func,442,CODE);	Template(Func,443,CODE);	\
		Template(Func,444,CODE);	Template(Func,445,CODE);	Template(Func,446,CODE);	Template(Func,447,CODE);	\
		Template(Func,448,CODE);	Template(Func,449,CODE);	Template(Func,450,CODE);	Template(Func,451,CODE);	\
		Template(Func,452,CODE);	Template(Func,453,CODE);	Template(Func,454,CODE);	Template(Func,455,CODE);	\
		Template(Func,456,CODE);	Template(Func,457,CODE);	Template(Func,458,CODE);	Template(Func,459,CODE);	\
		Template(Func,460,CODE);	Template(Func,461,CODE);	Template(Func,462,CODE);	Template(Func,463,CODE);	\
		Template(Func,464,CODE);	Template(Func,465,CODE);	Template(Func,466,CODE);	Template(Func,467,CODE);	\
		Template(Func,468,CODE);	Template(Func,469,CODE);	Template(Func,470,CODE);	Template(Func,471,CODE);	\
		Template(Func,472,CODE);	Template(Func,473,CODE);	Template(Func,474,CODE);	Template(Func,475,CODE);	\
		Template(Func,476,CODE);	Template(Func,477,CODE);	Template(Func,478,CODE);	Template(Func,479,CODE);	\
		Template(Func,480,CODE);	Template(Func,481,CODE);	Template(Func,482,CODE);	Template(Func,483,CODE);	\
		Template(Func,484,CODE);	Template(Func,485,CODE);	Template(Func,486,CODE);	Template(Func,487,CODE);	\
		Template(Func,488,CODE);	Template(Func,489,CODE);	Template(Func,490,CODE);	Template(Func,491,CODE);	\
		Template(Func,492,CODE);	Template(Func,493,CODE);	Template(Func,494,CODE);	Template(Func,495,CODE);	\
		Template(Func,496,CODE);	Template(Func,497,CODE);	Template(Func,498,CODE);	Template(Func,499,CODE);	\
		Template(Func,500,CODE);	Template(Func,501,CODE);	Template(Func,502,CODE);	Template(Func,503,CODE);	\
		Template(Func,504,CODE);	Template(Func,505,CODE);	Template(Func,506,CODE);	Template(Func,507,CODE);	\
		Template(Func,508,CODE);	Template(Func,509,CODE);	Template(Func,510,CODE);	Template(Func,511,CODE);

#endif

#endif /* _SIMDMSAIMMN512_511_H_ */
