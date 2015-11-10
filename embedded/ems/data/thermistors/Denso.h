/*
 * This file is part of EmsBench.
 *
 * Copyright 2015 University of Augsburg
 *
 * EmsBench is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EmsBench is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EmsBench.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * $Id: header-ems.c 480 2015-10-27 12:42:40Z klugeflo $
 * @file Denso.h
 * @ingroup dataInitialisers
 *
 * @brief Denso Coolant/Head / Inlet Air Temperature Transfer Table Data
 *
 * This file only contains the data to be hash included into the thermistor
 * table files for car specific builds.
 *
 *<h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

65535, 65535, 65535, 60641, 57372, 55074, 53332, 51945, 50803, 49837, 49004, 48276, 47629, 47051, 46527, 46051,
       45614, 45211, 44838, 44491, 44166, 43862, 43576, 43306, 43051, 42809, 42579, 42360, 42151, 41952, 41760, 41577,
       41401, 41232, 41070, 40913, 40761, 40615, 40474, 40337, 40205, 40077, 39952, 39831, 39714, 39600, 39489, 39381,
       39275, 39173, 39073, 38975, 38880, 38787, 38696, 38607, 38520, 38435, 38352, 38270, 38191, 38112, 38036, 37960,
       37887, 37814, 37743, 37674, 37605, 37538, 37472, 37407, 37343, 37280, 37218, 37157, 37097, 37039, 36981, 36923,
       36867, 36812, 36757, 36703, 36650, 36598, 36546, 36495, 36445, 36396, 36347, 36298, 36251, 36204, 36157, 36112,
       36066, 36022, 35977, 35934, 35891, 35848, 35806, 35764, 35723, 35682, 35642, 35602, 35562, 35523, 35485, 35447,
       35409, 35371, 35334, 35298, 35261, 35225, 35190, 35155, 35120, 35085, 35051, 35017, 34983, 34950, 34917, 34884,
       34852, 34820, 34788, 34756, 34725, 34694, 34663, 34633, 34602, 34572, 34543, 34513, 34484, 34455, 34426, 34397,
       34369, 34341, 34313, 34285, 34258, 34230, 34203, 34176, 34150, 34123, 34097, 34071, 34045, 34019, 33993, 33968,
       33943, 33918, 33893, 33868, 33843, 33819, 33795, 33771, 33747, 33723, 33699, 33676, 33653, 33630, 33606, 33584,
       33561, 33538, 33516, 33493, 33471, 33449, 33427, 33405, 33384, 33362, 33341, 33319, 33298, 33277, 33256, 33235,
       33215, 33194, 33174, 33153, 33133, 33113, 33093, 33073, 33053, 33033, 33014, 32994, 32975, 32955, 32936, 32917,
       32898, 32879, 32860, 32841, 32823, 32804, 32786, 32767, 32749, 32731, 32712, 32694, 32676, 32659, 32641, 32623,
       32605, 32588, 32570, 32553, 32536, 32518, 32501, 32484, 32467, 32450, 32433, 32416, 32400, 32383, 32366, 32350,
       32333, 32317, 32301, 32284, 32268, 32252, 32236, 32220, 32204, 32188, 32172, 32157, 32141, 32125, 32110, 32094,
       32079, 32063, 32048, 32033, 32018, 32002, 31987, 31972, 31957, 31942, 31927, 31913, 31898, 31883, 31868, 31854,
       31839, 31825, 31810, 31796, 31781, 31767, 31753, 31739, 31724, 31710, 31696, 31682, 31668, 31654, 31640, 31626,
       31613, 31599, 31585, 31571, 31558, 31544, 31531, 31517, 31504, 31490, 31477, 31464, 31450, 31437, 31424, 31411,
       31397, 31384, 31371, 31358, 31345, 31332, 31319, 31306, 31294, 31281, 31268, 31255, 31243, 31230, 31217, 31205,
       31192, 31180, 31167, 31155, 31142, 31130, 31117, 31105, 31093, 31080, 31068, 31056, 31044, 31032, 31020, 31008,
       30995, 30983, 30971, 30960, 30948, 30936, 30924, 30912, 30900, 30888, 30877, 30865, 30853, 30841, 30830, 30818,
       30807, 30795, 30784, 30772, 30761, 30749, 30738, 30726, 30715, 30703, 30692, 30681, 30670, 30658, 30647, 30636,
       30625, 30613, 30602, 30591, 30580, 30569, 30558, 30547, 30536, 30525, 30514, 30503, 30492, 30481, 30470, 30460,
       30449, 30438, 30427, 30416, 30406, 30395, 30384, 30374, 30363, 30352, 30342, 30331, 30320, 30310, 30299, 30289,
       30278, 30268, 30257, 30247, 30236, 30226, 30216, 30205, 30195, 30185, 30174, 30164, 30154, 30143, 30133, 30123,
       30113, 30102, 30092, 30082, 30072, 30062, 30052, 30041, 30031, 30021, 30011, 30001, 29991, 29981, 29971, 29961,
       29951, 29941, 29931, 29921, 29911, 29902, 29892, 29882, 29872, 29862, 29852, 29842, 29833, 29823, 29813, 29803,
       29794, 29784, 29774, 29764, 29755, 29745, 29735, 29726, 29716, 29707, 29697, 29687, 29678, 29668, 29659, 29649,
       29639, 29630, 29620, 29611, 29601, 29592, 29582, 29573, 29563, 29554, 29545, 29535, 29526, 29516, 29507, 29498,
       29488, 29479, 29470, 29460, 29451, 29442, 29432, 29423, 29414, 29404, 29395, 29386, 29377, 29367, 29358, 29349,
       29340, 29330, 29321, 29312, 29303, 29294, 29284, 29275, 29266, 29257, 29248, 29239, 29230, 29221, 29211, 29202,
       29193, 29184, 29175, 29166, 29157, 29148, 29139, 29130, 29121, 29112, 29103, 29094, 29085, 29076, 29067, 29058,
       29049, 29040, 29031, 29022, 29013, 29004, 28995, 28986, 28977, 28968, 28959, 28950, 28942, 28933, 28924, 28915,
       28906, 28897, 28888, 28879, 28870, 28862, 28853, 28844, 28835, 28826, 28817, 28809, 28800, 28791, 28782, 28773,
       28764, 28756, 28747, 28738, 28729, 28720, 28712, 28703, 28694, 28685, 28677, 28668, 28659, 28650, 28642, 28633,
       28624, 28615, 28607, 28598, 28589, 28580, 28572, 28563, 28554, 28545, 28537, 28528, 28519, 28510, 28502, 28493,
       28484, 28476, 28467, 28458, 28449, 28441, 28432, 28423, 28415, 28406, 28397, 28389, 28380, 28371, 28362, 28354,
       28345, 28336, 28328, 28319, 28310, 28302, 28293, 28284, 28276, 28267, 28258, 28249, 28241, 28232, 28223, 28215,
       28206, 28197, 28189, 28180, 28171, 28163, 28154, 28145, 28136, 28128, 28119, 28110, 28102, 28093, 28084, 28076,
       28067, 28058, 28049, 28041, 28032, 28023, 28015, 28006, 27997, 27988, 27980, 27971, 27962, 27954, 27945, 27936,
       27927, 27919, 27910, 27901, 27892, 27884, 27875, 27866, 27857, 27849, 27840, 27831, 27822, 27813, 27805, 27796,
       27787, 27778, 27769, 27761, 27752, 27743, 27734, 27725, 27717, 27708, 27699, 27690, 27681, 27672, 27663, 27655,
       27646, 27637, 27628, 27619, 27610, 27601, 27592, 27584, 27575, 27566, 27557, 27548, 27539, 27530, 27521, 27512,
       27503, 27494, 27485, 27476, 27467, 27458, 27449, 27440, 27431, 27422, 27413, 27404, 27395, 27386, 27377, 27368,
       27359, 27349, 27340, 27331, 27322, 27313, 27304, 27295, 27286, 27276, 27267, 27258, 27249, 27240, 27230, 27221,
       27212, 27203, 27193, 27184, 27175, 27166, 27156, 27147, 27138, 27128, 27119, 27109, 27100, 27091, 27081, 27072,
       27062, 27053, 27044, 27034, 27025, 27015, 27006, 26996, 26987, 26977, 26968, 26958, 26948, 26939, 26929, 26920,
       26910, 26900, 26891, 26881, 26871, 26861, 26852, 26842, 26832, 26822, 26813, 26803, 26793, 26783, 26773, 26763,
       26753, 26744, 26734, 26724, 26714, 26704, 26694, 26684, 26674, 26664, 26653, 26643, 26633, 26623, 26613, 26603,
       26592, 26582, 26572, 26562, 26551, 26541, 26531, 26520, 26510, 26500, 26489, 26479, 26468, 26458, 26447, 26437,
       26426, 26415, 26405, 26394, 26383, 26373, 26362, 26351, 26340, 26330, 26319, 26308, 26297, 26286, 26275, 26264,
       26253, 26242, 26231, 26220, 26209, 26198, 26186, 26175, 26164, 26153, 26141, 26130, 26119, 26107, 26096, 26084,
       26073, 26061, 26049, 26038, 26026, 26014, 26003, 25991, 25979, 25967, 25955, 25943, 25931, 25919, 25907, 25895,
       25883, 25870, 25858, 25846, 25833, 25821, 25809, 25796, 25784, 25771, 25758, 25746, 25733, 25720, 25707, 25694,
       25681, 25668, 25655, 25642, 25629, 25616, 25602, 25589, 25576, 25562, 25549, 25535, 25521, 25508, 25494, 25480,
       25466, 25452, 25438, 25424, 25410, 25395, 25381, 25367, 25352, 25337, 25323, 25308, 25293, 25278, 25263, 25248,
       25233, 25218, 25202, 25187, 25171, 25156, 25140, 25124, 25108, 25092, 25076, 25060, 25043, 25027, 25010, 24994,
       24977, 24960, 24943, 24926, 24908, 24891, 24873, 24856, 24838, 24820, 24802, 24783, 24765, 24746, 24728, 24709,
       24690, 24670, 24651, 24632, 24612, 24592, 24572, 24551, 24531, 24510, 24489, 24468, 24447, 24425, 24403, 24381,
       24359, 24336, 24313, 24290, 24267, 24243, 24219, 24195, 24170, 24146, 24120, 24095, 24069, 24042, 24016, 23989,
       23961, 23933, 23905, 23876, 23847, 23817, 23786, 23755, 23724, 23692, 23659, 23626, 23592, 23557, 23521, 23485,
       23448, 23410, 23371, 23330, 23289, 23247, 23203, 23159, 23112, 23065, 23015, 22964, 22911, 22856, 22798, 22738,
       22675, 22609, 22540, 22466, 22388, 22305, 22215, 22119, 22013, 21897, 21766, 21618, 21444, 21232, 20957, 20545
