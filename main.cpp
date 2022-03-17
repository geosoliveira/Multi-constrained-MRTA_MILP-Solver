#include <ilcplex/ilocplex.h>
#include <cmath>
#include <cstdlib>

using namespace std;

ILOSTLBEGIN

typedef struct NODE {
	uint16_t x;
	uint16_t y;
	uint16_t height;
	double demand;
} node_t;

typedef struct ROBOT {
	double capacity;
	double traffic_speed;
	double lifting_speed;
} robot_t;

typedef IloArray<IloNumVarArray> NumVarMatrix;
typedef IloArray<NumVarMatrix>   NumVar3Matrix;
typedef IloArray<NumVar3Matrix>  NumVar4Matrix;
typedef IloArray<IloExprArray>   ExprMatrix;
typedef IloArray<ExprMatrix>     Expr3Matrix;
typedef IloArray<Expr3Matrix>     Expr4Matrix;

/*node_t nodes[] = {
	{ 49, 49, 0, 30.0, 0.0 },{ 20, 26, 0, 9.0, 0.0 },{ 21, 47, 0, 15.0, 0.0 },
	{ 31, 62, 0, 23.0, 0.0 },{ 51, 21, 0, 5.0, 0.0 },{ 31, 32, 0, 29.0, 0.0 },
	{ 12, 42, 0, 21.0, 0.0 },{ 52, 41, 0, 15.0, 0.0 },{ 17, 33, 0, 41.0, 0.0 },
	{ 57, 58, 0, 28.0, 0.0 },{ 37, 52, 0, 0.0, 7.0 },{ 52, 64, 0, 0.0, 16.0 },
	{ 40, 30, 0, 0.0, 21.0 },{ 17, 63, 0, 0.0, 19.0 },{ 52, 33, 0, 0.0, 11.0 },
	{ 42, 41, 0, 0.0, 19.0 },{ 5, 25, 0, 0.0, 23.0 },{ 36, 16, 0, 0.0, 10.0 },
	{ 27, 23, 0, 0.0, 3.0 },{ 13, 13, 0, 0.0, 9.0 },{ 30, 40, 0, 0.0, 0.0 },
	{ 50, 30, 0, 0.0, 0.0 }
};

robot_t robots[]{
	{ 20.0, 20.0, 17.2 },{ 30.0, 35.0, 21.2 },{ 40.0, 50.0, 25.2 },{ 70.0, 120.0, 26.2 },
	{ 120.0, 225.0, 28.4 }
};

int l = 10; //number of linehauls
int b = 10; //number of backhauls
int n = l + b; //number of customers
int m = 2; //number of depots
int K = 5; //number of robots*/

/*node_t nodes[] = {
	{ 146, 180, 1, 46, 0 },
	{ 792, 5, 1, 62, 0 },
	{ 658, 510, 1, 88, 0 },
	{ 461, 270, 1, 85, 0 },
	{ 299, 531, 1, 70, 0 },
	{ 812, 228, 1, 65, 0 },
	{ 643, 90, 1, 1, 0 },
	{ 615, 630, 1, 119, 0 },
	{ 258, 42, 1, 75, 0 },
	{ 616, 299, 1, 119, 0 },
	/*{ 475, 957, 1, 30, 0 },
	{ 425, 473, 1, 104, 0 },
	{ 406, 64, 1, 56, 0 },
	{ 656, 369, 1, 33, 0 },
	{ 202, 467, 1, 21, 0 },
	{ 318, 21, 1, 117, 0 },
	{ 579, 587, 1, 90, 0 },
	{ 458, 354, 1, 98, 0 },
	{ 575, 871, 1, 75, 0 },
	{ 47, 512, 1, 71, 0 },
	/*{ 568, 742, 1, 28, 0 },
	{ 128, 436, 1, 75, 0 },
	{ 546, 806, 1, 80, 0 },
	{ 197, 696, 1, 42, 0 },
	{ 615, 300, 1, 64, 0 },
	{ 852, 563, 1, 22, 0 },
	{ 772, 803, 1, 105, 0 },
	{ 678, 342, 1, 39, 0 },
	{ 916, 176, 1, 5, 0 },
	{ 390, 949, 1, 74, 0 },
	{ 113, 782, 1, 115, 0 },
	{ 226, 736, 1, 28, 0 },
	{ 119, 923, 1, 18, 0 },
	{ 584, 572, 1, 6, 0 },
	{ 134, 554, 1, 64, 0 },
	{ 912, 173, 1, 117, 0 },
	{ 827, 233, 1, 85, 0 },
	{ 851, 677, 1, 39, 0 },
	{ 598, 322, 1, 33, 0 },
	{ 627, 472, 1, 51, 0 },
	{ 94, 442, 1, 81, 0 },
	{ 688, 274, 1, 92, 0 },
	{ 977, 176, 1, 18, 0 },
	{ 597, 461, 1, 47, 0 },
	{ 931, 23, 1, 17, 0 },
	{ 170, 640, 1, 52, 0 },
	{ 941, 601, 1, 13, 0 },
	{ 873, 487, 1, 113, 0 },
	{ 797, 95, 1, 64, 0 },
	{ 451, 816, 1, 53, 0 },
	/*{ 866, 970, 1, 97, 0 },
	{ 833, 912, 1, 105, 0 },
	{ 106, 913, 1, 117, 0 },
	{ 260, 107, 1, 81, 0 },
	{ 332, 45, 1, 87, 0 },
	{ 685, 613, 1, 60, 0 },
	{ 728, 372, 1, 10, 0 },
	{ 487, 497, 1, 70, 0 },
	{ 702, 440, 1, 67, 0 },
	{ 717, 412, 1, 81, 0 },
	{ 635, 794, 1, 108, 0 },
	{ 927, 972, 1, 46, 0 },
	{ 635, 356, 1, 79, 0 },
	{ 634, 540, 1, 4, 0 },
	{ 658, 261, 1, 6, 0 },
	{ 303, 168, 1, 56, 0 },
	{ 707, 410, 1, 121, 0 },
	{ 254, 135, 1, 63, 0 },
	{ 346, 29, 1, 34, 0 },
	{ 75, 79, 1, 116, 0 },
	{ 893, 987, 1, 22, 0 },
	{ 729, 372, 1, 19, 0 },
	{ 29, 910, 1, 8, 0 },
	{ 356, 39, 1, 88, 0 },
	{ 274, 943, 1, 92, 0 },
	{ 322, 96, 1, 7, 0 },
	{ 664, 396, 1, 77, 0 },
	{ 704, 236, 1, 47, 0 },
	{ 415, 837, 1, 104, 0 },
	{ 576, 587, 1, 85, 0 },
	{ 750, 977, 1, 17, 0 },
	{ 726, 363, 1, 100, 0 },
	{ 861, 948, 1, 116, 0 },
	{ 302, 129, 1, 52, 0 },
	{ 415, 989, 1, 15, 0 },
	{ 199, 135, 1, 88, 0 },
	{ 801, 405, 1, 2, 0 },
	{ 679, 426, 1, 25, 0 },
	{ 994, 804, 1, 22, 0 },
	{ 311, 116, 1, 67, 0 },
	{ 739, 898, 1, 91, 0 },
	{ 268, 97, 1, 82, 0 },
	{ 176, 991, 1, 121, 0 },
	{ 688, 588, 1, 74, 0 },
	{ 107, 836, 1, 29, 0 },
	{ 708, 522, 1, 48, 0 },
	{ 679, 864, 1, 58, 0 },
	{ 985, 877, 1, 62, 0 },
	{ 954, 950, 1, 94, 0 },
	{ 615, 750, 1, 42, 0 },*/

	/*{ 365, 689, 0, 0, 300},
	{ 407, 253, 0, 0, 300 },
	/*{ 783, 197, 0, 0, 100 },
	{ 454, 771, 0, 0, 100 },*/

	/*{ 268, 614, 0, 0, 0},
	/*{ 512, 976, 0, 0, 0 },
	{ 312, 619, 0, 0, 0},
	{ 311, 744, 0, 0, 0},
	{ 132, 918, 0, 0, 0},
	{ 956, 169, 0, 0, 0 },
	{ 627, 966, 0, 0, 0 },
	{ 210, 340, 0, 0, 0 },
	{ 56, 517, 0, 0, 0 },
	{ 181, 184, 0, 0, 0 },
	/*{ 392, 251, 0, 0, 0 },
	{ 161, 470, 0, 0, 0 },
	{ 557, 868, 0, 0, 0 },
	{ 415, 442, 0, 0, 0 },
	{ 831, 641, 0, 0, 0 },
	{ 283, 182, 0, 0, 0 },
	{ 384, 745, 0, 0, 0 },
	{ 150, 202, 0, 0, 0 },
	{ 647, 215, 0, 0, 0 },
	{ 364, 357, 0, 0, 0 },
	{ 653, 921, 0, 0, 0 },
	{ 324, 757, 0, 0, 0 },
	{ 686, 783, 0, 0, 0 },
	{ 110, 101, 0, 0, 0 },
	{ 671, 812, 0, 0, 0 },*/

	/*{ 365, 689, 0, 0, 300},
	{ 407, 253, 0, 0, 300 }/*,
	{ 783, 197, 0, 0, 300 },
	{ 454, 771, 0, 0, 300 }*/
/*};

robot_t robots[]{
	{ 200, 1, 1 }/*,{ 235, 1, 1 }/*,{ 250, 1, 1 },{ 300, 1, 1 },{ 500, 1, 1 },
	{ 250, 1, 1 },{ 250, 1, 1 },{ 250, 1, 1 },{ 250, 1, 1 },{ 250, 1, 1 }/*,
	{ 300, 1, 1 },{ 300, 1, 1 },{ 300, 1, 1 },{ 300, 1, 1 },{ 250, 1, 1 },
	{ 250, 1, 1 },{ 250, 1, 1 },{ 200, 1, 1 },{ 200, 1, 1 },{ 200, 1, 1 },
	{ 300, 1, 1 },{ 235, 1, 1 },{ 235, 1, 1 },{ 235, 1, 1 },{ 235, 1, 1 },
	{ 235, 1, 1 },{ 235, 1, 1 },{ 235, 1, 1 },{ 235, 1, 1 },{ 250, 1, 1 }*/
/*};

int nPickTasks = 10; //number of picking tasks
int nDeliveries = 2; //number of delivery tasks
int nTasks = nPickTasks + nDeliveries; //number of tasks
int nStarts = 1; //number of starting robot position (same the number of robots)
int nRobots = 1; //number of robots
int nBacks = 2; //number of backpoints*/

#define STREAM_SIZE 512

node_t* nodes;
robot_t* robots;
int nPickTasks;
int nDeliveries;
int nTasks;
int nStarts;
int nRobots;
int nBacks;

void parse_file(std::string in_filename) {
	int automata_state = 0, curr_pick_task, curr_deliver_task, curr_robot;
	uint16_t x, y, curr_height;
	char stream[STREAM_SIZE];

	ifstream in_stream;
	in_stream.open(in_filename.c_str(), ios::in);

	if (!in_stream) {
		fprintf(stderr, "Can't open input file %s. Exiting...\n", in_filename.c_str());
		exit(1);
	}

	while (!in_stream.eof()) {
		in_stream >> stream;
		switch (automata_state) {
		case 0:
			if (!strcmp(stream, "NAME")) {
				automata_state = 1;
			}
			break;
		case 1:
			automata_state = 2;
			break;
		case 2:
			automata_state = 3;
			break;
		case 3:
			if (!strcmp(stream, "DIMENSION")) {
				automata_state = 4;
			}
			break;
		case 4:
			automata_state = 5;
			break;
		case 5:
			nPickTasks = atoi(stream);
			automata_state = 6;
			break;
		case 6:
			if (!strcmp(stream, "N_ROBOTS")) {
				automata_state = 7;
			}
			break;
		case 7:
			automata_state = 8;
			break;
		case 8:
			nRobots = atoi(stream);
			nStarts = nRobots;
			robots = new robot_t[nRobots];
			automata_state = 9;
			break;
		case 9:
			if (!strcmp(stream, "N_DELIVERIES")) {
				automata_state = 10;
			}
			break;
		case 10:
			automata_state = 11;
			break;
		case 11:
			nDeliveries = atoi(stream);
			nBacks = nDeliveries;
			nTasks = nPickTasks + nDeliveries;
			nodes = new node_t[nTasks + nStarts + nBacks];
			automata_state = 12;
			break;
		case 12:
			if (!strcmp(stream, "EDGE_WEIGHT_TYPE")) {
				automata_state = 13;
			}
			break;
		case 13:
			automata_state = 14;
			break;
		case 14:
			automata_state = 15;
			break;
		case 15:
			if (!strcmp(stream, "N_TASKS_IT")) {
				automata_state = 16;
			}
			break;
		case 16:
			automata_state = 17;
			break;
		case 17:
			if (!strcmp(stream, "NODE_COORD_SECTION")) {
				automata_state = 18;
			}
			else {
				automata_state = 17;
			}
			break;
		case 18:
			curr_pick_task = atoi(stream);
			automata_state = 19;
			break;
		case 19:
			x = atoi(stream);
			nodes[curr_pick_task - 1].x = x;
			automata_state = 20;
			break;
		case 20:
			y = atoi(stream);
			nodes[curr_pick_task - 1].y = y;
			automata_state = 21;
			break;
		case 21:
			curr_height = atoi(stream);
			nodes[curr_pick_task - 1].height = curr_height;
			automata_state = 22;
			break;
		case 22:
			automata_state = 23;
			break;
		case 23:
			if (!strcmp(stream, "DEMAND_SECTION")) {
				automata_state = 28;
			}
			else {
				curr_pick_task = atoi(stream);
				automata_state = 24;
			}
			break;
		case 24:
			x = atoi(stream);
			nodes[curr_pick_task - 1].x = x;
			automata_state = 25;
			break;
		case 25:
			y = atoi(stream);
			nodes[curr_pick_task - 1].y = y;
			automata_state = 26;
			break;
		case 26:
			curr_height = atoi(stream);
			nodes[curr_pick_task - 1].height = curr_height;
			automata_state = 27;
			break;
		case 27:
			automata_state = 23;
			break;
		case 28:
			curr_pick_task = atoi(stream);
			automata_state = 29;
			break;
		case 29:
			nodes[curr_pick_task - 1].demand = atof(stream);
			automata_state = 30;
			break;
		case 30:
			if (!strcmp(stream, "ROBOT_SECTION")) {
				automata_state = 32;
			}
			else {
				curr_pick_task = atoi(stream);
				automata_state = 31;
			}
			break;
		case 31:
			nodes[curr_pick_task - 1].demand = atof(stream);
			automata_state = 30;
			break;
		case 32:
			curr_robot = atoi(stream);
			automata_state = 33;
			break;
		case 33:
			automata_state = 34;
			break;
		case 34:
			x = atoi(stream);
			nodes[nTasks + curr_robot - 1].x = x;
			automata_state = 35;
			break;
		case 35:
			y = atoi(stream);
			nodes[nTasks + curr_robot - 1].y = y;
			automata_state = 36;
			break;
		case 36:
			robots[curr_robot - 1].capacity = atof(stream);
			automata_state = 37;
			break;
		case 37:
			robots[curr_robot - 1].traffic_speed = atof(stream);
			automata_state = 38;
			break;
		case 38:
			robots[curr_robot - 1].lifting_speed = atof(stream);
			automata_state = 39;
			break;
		case 39:
			if (!strcmp(stream, "DELIVERY_SECTION")) {
				automata_state = 46;
			}
			else {
				curr_robot = atoi(stream);
				automata_state = 40;
			}
			break;
		case 40:
			automata_state = 41;
			break;
		case 41:
			x = atoi(stream);
			nodes[nTasks + curr_robot - 1].x = x;
			automata_state = 42;
			break;
		case 42:
			y = atoi(stream);
			nodes[nTasks + curr_robot - 1].y = y;
			automata_state = 43;
			break;
		case 43:
			robots[curr_robot - 1].capacity = atof(stream);
			automata_state = 44;
			break;
		case 44:
			robots[curr_robot - 1].traffic_speed = atof(stream);
			automata_state = 45;
			break;
		case 45:
			robots[curr_robot - 1].lifting_speed = atof(stream);
			automata_state = 39;
			break;
		case 46:
			curr_deliver_task = atoi(stream);
			automata_state = 47;
			break;
		case 47:
			x = atoi(stream);
			nodes[nPickTasks + curr_deliver_task - 1].x = x;
			nodes[nTasks + nStarts + curr_deliver_task - 1].x = x;
			automata_state = 48;
			break;
		case 48:
			y = atoi(stream);
			nodes[nPickTasks + curr_deliver_task - 1].y = y;
			nodes[nTasks + nStarts + curr_deliver_task - 1].y = y;
			automata_state = 49;
			break;
		case 49:
			nodes[nPickTasks + curr_deliver_task - 1].demand = atof(stream);
			nodes[nTasks + nStarts + curr_deliver_task - 1].demand = atof(stream);
			nodes[nPickTasks + curr_deliver_task - 1].height = 0;
			nodes[nTasks + nStarts + curr_deliver_task - 1].height = 0;
			automata_state = 50;
			break;
		case 50:
			if (!strcmp(stream, "EOF")) {
				automata_state = 54;
			}
			else {
				curr_deliver_task = atoi(stream);
				automata_state = 51;
			}
			break;
		case 51:
			x = atoi(stream);
			nodes[nPickTasks + curr_deliver_task - 1].x = x;
			nodes[nTasks + nStarts + curr_deliver_task - 1].x = x;
			automata_state = 52;
			break;
		case 52:
			y = atoi(stream);
			nodes[nPickTasks + curr_deliver_task - 1].y = y;
			nodes[nTasks + nStarts + curr_deliver_task - 1].y = y;
			automata_state = 53;
			break;
		case 53:
			nodes[nPickTasks + curr_deliver_task - 1].demand = atof(stream);
			nodes[nTasks + nStarts + curr_deliver_task - 1].demand = atof(stream);
			nodes[nPickTasks + curr_deliver_task - 1].height = 0;
			nodes[nTasks + nStarts + curr_deliver_task - 1].height = 0;
			automata_state = 50;
			break;
		case 54:
			break;
		default:
			break;
		}
	}
	in_stream.close();
	
	return;
}



float distance_of(int _node1, int _node2) {
	//return sqrt(pow(float(nodes[_node1].x - nodes[_node2].x), 2.0) + pow(float(nodes[_node1].y - nodes[_node2].y), 2.0));
	return float(abs(nodes[_node1].x - nodes[_node2].x) + abs(nodes[_node1].y - nodes[_node2].y));
}

double max_capacity() {
	double maximum = 0.0;
	for (size_t i = 0; i < nTasks; i++) {
		if (robots[i].capacity > maximum) {
			maximum = robots[i].capacity;
		}
	}
	return maximum;
}

int main(int argc, char** argv) {

	if (argc != 4) {
		cerr << "Usage: " << argv[0] << " <input-file> [solve_time] [print_solution]" << endl;
		exit(1);
	}

	parse_file(argv[1]);

	long solve_time = atol(argv[2]);
	bool print_solution = bool(atoi(argv[3]));

	IloEnv env;
	IloModel model(env);

	if (print_solution) cout << "Initializing w..." << endl;
	NumVarMatrix w(env, nTasks - nPickTasks);
	for (int i = nPickTasks; i < nTasks; i++) {
		w[i - nPickTasks] = IloNumVarArray(env, nRobots, 0.0, max_capacity(), ILOFLOAT);
	}

	if (print_solution) cout << "Initializing x..." << endl;
	// Initialize 4-D matrix x;
	NumVar4Matrix x(env, nTasks + nStarts + nBacks);
	for (int i = 0; i < nTasks + nStarts + nBacks; i++) {
		x[i] = NumVar3Matrix(env, nTasks + nStarts + nBacks);
		for (int j = 0; j < nTasks + nStarts + nBacks; j++) {
			x[i][j] = NumVarMatrix(env, nRobots);
			for (int k = 0; k < nRobots; k++) {
				x[i][j][k] = IloNumVarArray(env, nStarts, 0, 1, ILOBOOL);
			}
		}
	}

	if (print_solution) cout << "Initializing y..." << endl;
	// Initialize matrix Y;
	NumVar3Matrix y(env, nRobots);
	for (int k = 0; k < nRobots; k++) {
		y[k] = NumVarMatrix(env, nTasks + nStarts + nBacks);
		for (int i = 0; i < nTasks + nStarts + nBacks; i++) {
			y[k][i] = IloNumVarArray(env, nTasks + nStarts + nBacks, 0.0, max_capacity(), ILOFLOAT);
		}
	}

	if (print_solution) cout << "Expression 1..." << endl;
	// Dado um picktask, o número de chegadas é 1, independentemente do robô
	IloExprArray expr1(env, nPickTasks);
	for (int j = 0; j < nPickTasks; j++) { //picktask
		expr1[j] = IloExpr(env);
		for (int d = nTasks; d < nTasks + nStarts; d++) {
			for (int k = 0; k < nRobots; k++) {
				for (int i = 0; i < nTasks + nStarts + nBacks; i++) {
					expr1[j] += x[i][j][k][d - nTasks];
				}
			}
		}
		model.add(expr1[j] == 1);
		expr1[j].end();
	}

	if (print_solution) cout << "Expression 2..." << endl;
	// Dado um picktask, o número de saídas é 1, independentemente do robô
	IloExprArray expr2(env, nTasks);
	for (int i = 0; i < nPickTasks; i++) { //picktask
		expr2[i] = IloExpr(env);
		for (int d = nTasks; d < nTasks + nStarts; d++) {
			for (int k = 0; k < nRobots; k++) {
				for (int j = 0; j < nTasks + nStarts + nBacks; j++) {
					expr2[i] += x[i][j][k][d - nTasks];
				}
			}
		}
		model.add(expr2[i] == 1);
		expr2[i].end();
	}

	if (print_solution) cout << "Expression 3..." << endl;
	// Dado um delivery, o número de chegadas é de 0 a l
	IloExprArray expr3(env, nTasks - nPickTasks);
	for (int j = nPickTasks; j < nTasks; j++) { //delivery
		expr3[j - nPickTasks] = IloExpr(env);
		for (int d = nTasks; d < nTasks + nStarts; d++) {
			for (int k = 0; k < nRobots; k++) {
				for (int i = 0; i < nTasks + nStarts + nBacks; i++) {
					expr3[j - nPickTasks] += x[i][j][k][d - nTasks];
				}
			}
		}
		model.add(0 <= expr3[j - nPickTasks] <= nPickTasks);
		expr3[j - nPickTasks].end();
	}

	if (print_solution) cout << "Expression 4..." << endl;
	// Dado um delivery, o número de saídas é de 0 a l
	IloExprArray expr4(env, nTasks - nPickTasks);
	for (int i = nPickTasks; i < nTasks; i++) { //delivery
		expr4[i - nPickTasks] = IloExpr(env);
		for (int d = nTasks; d < nTasks + nStarts; d++) {
			for (int k = 0; k < nRobots; k++) {
				for (int j = 0; j < nTasks + nStarts + nBacks; j++) {
					expr4[i - nPickTasks] += x[i][j][k][d - nTasks];
				}
			}
		}
		model.add(0 <= expr4[i - nPickTasks] <= nPickTasks);
		expr4[i - nPickTasks].end();
	}

	if (print_solution) cout << "Expression 5..." << endl;
	// Dado um ponto de início, o número de chegadas é de 0
	IloExprArray expr5(env, nStarts);
	for (int j = nTasks; j < nTasks + nStarts; j++) { //ponto de inicio
		expr5[j - nTasks] = IloExpr(env);
		for (int d = nTasks; d < nTasks + nStarts; d++) {
			for (int k = 0; k < nRobots; k++) {
				for (int i = 0; i < nTasks + nStarts + nBacks; i++) { // qualquer ponto
					expr5[j - nTasks] += x[i][j][k][d - nTasks];
				}
			}
		}
		model.add(expr5[j - nTasks] == 0);
		expr5[j - nTasks].end();
	}

	if (print_solution) cout << "Expression 6..." << endl;
	// Dado um ponto de início, o número de saídas é de 1 a K  (nem todos os robôs serão usados)
	IloExprArray expr6(env, nStarts);
	for (int i = nTasks; i < nTasks + nStarts; i++) { //ponto de inicio
		expr6[i - nTasks] = IloExpr(env);
		for (int d = nTasks; d < nTasks + nStarts; d++) {
			for (int k = 0; k < nRobots; k++) {
				for (int j = 0; j < nTasks + nStarts + nBacks; j++) { // qualquer ponto
					expr6[i - nTasks] += x[i][j][k][d - nTasks];
				}
			}
		}
		model.add(1 <= expr6[i - nTasks] <= nRobots);
		expr6[i - nTasks].end();
	}

	if (print_solution) cout << "Expression 7..." << endl;
	// Dado um backpoint, o número de chegadas é de 0 a l
	IloExprArray expr7(env, nBacks);
	for (int j = nTasks + nStarts; j < nTasks + nStarts + nBacks; j++) { //backpoint
		expr7[j - nTasks - nStarts] = IloExpr(env);
		for (int d = nTasks; d < nTasks + nStarts; d++) {
			for (int k = 0; k < nRobots; k++) {
				for (int i = 0; i < nTasks + nStarts + nBacks; i++) {
					expr7[j - nTasks - nStarts] += x[i][j][k][d - nTasks];
				}
			}
		}
		model.add(0 <= expr7[j - nTasks - nStarts] <= nPickTasks);
		expr7[j - nTasks - nStarts].end();
	}

	if (print_solution) cout << "Expression 8..." << endl;
	// Dado um backpoint, o número de saídas é de 0 a l
	IloExprArray expr8(env, nBacks);
	for (int i = nTasks + nStarts; i < nTasks + nStarts + nBacks; i++) { //backpoint
		expr8[i - nTasks - nStarts] = IloExpr(env);
		for (int d = nTasks; d < nTasks + nStarts; d++) {
			for (int k = 0; k < nRobots; k++) {
				for (int j = 0; j < nTasks + nStarts + nBacks; j++) { // picktask
					expr8[i - nTasks - nStarts] += x[i][j][k][d - nTasks];
				}
			}
		}
		model.add(0 <= expr8[i - nTasks - nStarts] <= nPickTasks);
		expr8[i - nTasks - nStarts].end();
	}

	if (print_solution) cout << "Expression 9..." << endl;
	// A carga restabelecida após executar um delivery task é definida aqui
	Expr3Matrix expr9(env, nRobots);
	for (int k = 0; k < nRobots; k++) {
		expr9[k] = ExprMatrix(env, nTasks - nPickTasks);
		for (int j = nPickTasks; j < nTasks; j++) {
			expr9[k][j - nPickTasks] = IloExprArray(env, nStarts);
			for (int d = nTasks; d < nTasks + nStarts; d++) {
				expr9[k][j - nPickTasks][d - nTasks] = IloExpr(env);
				for (int i = 0; i < nPickTasks; i++) {
					expr9[k][j - nPickTasks][d - nTasks] += nodes[i].demand * x[i][j][k][d - nTasks];
				}
				model.add(w[j - nPickTasks][k] == robots[k].capacity - expr9[k][j - nPickTasks][d - nTasks]);
				expr9[k][j - nPickTasks][d - nTasks].end();
			}
		}
	}

	if (print_solution) cout << "Expression 10..." << endl;
	// Iguala a capacidade dos robôs partindo dos pontos de inicio e backpoints com a demanda de todas as tarefas
	IloExprArray expr10_1(env, nRobots);
	IloExprArray expr10_2(env, nRobots);
	for (int k = 0; k < nRobots; k++) {
		expr10_1[k] = IloExpr(env);
		expr10_2[k] = IloExpr(env);
		for (int i = nTasks; i < nTasks + nStarts + nBacks; i++) {
			for (int j = 0; j < nPickTasks; j++) {
				expr10_1[k] += y[k][i][j];
			}
		}
		for (int j = 0; j < nPickTasks; j++) {
			expr10_2[k] += nodes[j].demand;
		}
		model.add(expr10_1[k] == expr10_2[k]);
		expr10_1[k].end();
		expr10_2[k].end();
	}

	if (print_solution) cout << "Expression 11..." << endl;
	// Iguala a capacidade dos robôs partindo dos backpoints com a capacidade renovada nos delivery tasks
	IloExprArray expr11_1(env, nRobots);
	IloExprArray expr11_2(env, nRobots);
	for (int k = 0; k < nRobots; k++) {
		expr11_1[k] = IloExpr(env);
		expr11_2[k] = IloExpr(env);
		for (int i = nPickTasks; i < nTasks; i++) {
			for (int j = nTasks + nStarts; j < nTasks + nStarts + nBacks; j++) {
				expr11_1[k] += y[k][i][j];
			}
		}
		for (int i = nPickTasks; i < nTasks; i++) {
			expr11_2[k] += w[i - nPickTasks][k];
		}
		model.add(expr11_1[k] == expr11_2[k]);
		expr11_1[k].end();
		expr11_2[k].end();
	}

	if (print_solution) cout << "Expression 12..." << endl;
	// A capacidade restante de carga saindo de um pick task até um ponto qualquer é a capacidade restante 
	// que o robô tinha antes de chegar na pick task, somado com a sua demanda.
	ExprMatrix expr12_1(env, nRobots);
	ExprMatrix expr12_2(env, nRobots);
	ExprMatrix expr12_3(env, nRobots);
	for (int k = 0; k < nRobots; k++) {
		expr12_1[k] = IloExprArray(env, nPickTasks);
		expr12_2[k] = IloExprArray(env, nPickTasks);
		expr12_3[k] = IloExprArray(env, nPickTasks);
		for (int j = 0; j < nPickTasks; j++) {
			expr12_1[k][j] = IloExpr(env);
			expr12_2[k][j] = IloExpr(env);
			expr12_3[k][j] = IloExpr(env);
			for (int i = 0; i < nPickTasks; i++) {
				expr12_1[k][j] += y[k][i][j];
			}
			for (int i = nTasks; i < nTasks + nStarts + nBacks; i++) {
				expr12_2[k][j] += y[k][i][j];
			}
			for (int i = 0; i < nTasks; i++) {
				expr12_3[k][j] += y[k][j][i];
			}
			model.add(expr12_1[k][j] + expr12_2[k][j] == expr12_3[k][j] + nodes[j].demand);
			expr12_1[k][j].end();
			expr12_2[k][j].end();
			expr12_3[k][j].end();
		}
	}

	if (print_solution) cout << "Expression 13..." << endl;
	// A capacidade do robô após executar um delivery task é a capacidade que o robô tinha antes de chegar ao 
	// delivery, somado com a capacidade restabelecida.
	ExprMatrix expr13_1(env, nRobots);
	ExprMatrix expr13_2(env, nRobots);
	for (int k = 0; k < nRobots; k++) {
		expr13_1[k] = IloExprArray(env, nTasks - nPickTasks);
		expr13_2[k] = IloExprArray(env, nTasks - nPickTasks);
		for (int j = nPickTasks; j < nTasks; j++) {
			expr13_1[k][j - nPickTasks] = IloExpr(env);
			expr13_2[k][j - nPickTasks] = IloExpr(env);
			for (int i = nTasks + nStarts; i < nTasks + nStarts + nBacks; i++) {
				expr13_1[k][j - nPickTasks] += y[k][j][i];
			}
			for (int i = 0; i < nPickTasks; i++) {
				expr13_2[k][j - nPickTasks] += y[k][i][j];
			}
			model.add(expr13_1[k][j - nPickTasks] == expr13_2[k][j - nPickTasks] + w[j - nPickTasks][k]);
			expr13_1[k][j - nPickTasks].end();
			expr13_2[k][j - nPickTasks].end();
		}
	}

	if (print_solution) cout << "Expression 14..." << endl;
	// Garante que a carga transportada ao longo de qualquer arco não exceda a capacidade máxima do robô
	Expr3Matrix expr14(env, nRobots);
	for (int k2 = 0; k2 < nRobots; k2++) {
		expr14[k2] = ExprMatrix(env, nTasks + nStarts + nBacks);
		for (int i = 0; i < nTasks + nStarts + nBacks; i++) {
			expr14[k2][i] = IloExprArray(env, nTasks + nStarts + nBacks);
			for (int j = 0; j < nTasks + nStarts + nBacks; j++) {
				if (i != j) {
					expr14[k2][i][j] = IloExpr(env);
					for (int d = nTasks; d < nTasks + nStarts; d++) {
						for (int k = 0; k < nRobots; k++) {
							expr14[k2][i][j] += robots[k].capacity * x[i][j][k][d - nTasks];
						}
					}
					model.add(y[k2][i][j] <= expr14[k2][i][j]);
					expr14[k2][i][j].end();
				}
			}
		}
	}

	if (print_solution) cout << "Expression 15..." << endl;
	// Impede que haja transporte de carga para si mesmo
	for (int k = 0; k < nRobots; k++) {
		for (int i = 0; i < nTasks; i++) {
			model.add(y[k][i][i] == 0.0);
		}
	}

	if (print_solution) cout << "Expression 16..." << endl;
	// Proibido ponto inicial para delivery, outro ponto inicial e backpoint
	for (int d = nTasks; d < nTasks + nStarts; d++) {
		for (int k = 0; k < nRobots; k++) {
			for (int i = nTasks; i < nTasks + nStarts; i++) {
				for (int j = nPickTasks; j < nTasks + nStarts + nBacks; j++) {
					model.add(x[i][j][k][d - nTasks] == 0);
				}
			}
		}
	}

	if (print_solution) cout << "Expression 17..." << endl;
	// Proibido picktask para ponto inicial e backpoint
	for (int d = nTasks; d < nTasks + nStarts; d++) {
		for (int k = 0; k < nRobots; k++) {
			for (int i = 0; i < nPickTasks; i++) {
				for (int j = nTasks; j < nTasks + nStarts + nBacks; j++) {
					model.add(x[i][j][k][d - nTasks] == 0);
				}
			}
		}
	}

	if (print_solution) cout << "Expression 18..." << endl;
	// Proibido delivery para ponto inicial, picktask e outro delivery
	for (int d = nTasks; d < nTasks + nStarts; d++) {
		for (int k = 0; k < nRobots; k++) {
			for (int i = nPickTasks; i < nTasks; i++) {
				for (int j = 0; j < nTasks + nStarts; j++) {
					model.add(x[i][j][k][d - nTasks] == 0);
				}
			}
		}
	}

	if (print_solution) cout << "Expression 19..." << endl;
	// Proibido backpoint para ponto inicial, delivery e outro backpoint
	for (int d = nTasks; d < nTasks + nStarts; d++) {
		for (int k = 0; k < nRobots; k++) {
			for (int i = nTasks + nStarts; i < nTasks + nStarts + nBacks; i++) {
				for (int j = nPickTasks; j < nTasks + nStarts + nBacks; j++) {
					model.add(x[i][j][k][d - nTasks] == 0);
				}
			}
		}
	}

	if (print_solution) cout << "Expression 20..." << endl;
	// Essa expressão garante que o robô parta exatamente do seu ponto inicial, e não de outro robô
	for (int k = 0; k < nRobots; k++) {
		for (int j = 0; j < nPickTasks; j++) {
			for (int d = nTasks; d < nTasks + nStarts; d++) {
				if (k != d - nTasks)
					model.add(x[nTasks + k][j][k][d - nTasks] == 0);
			}
		}
	}

	if (print_solution) cout << "Expression 21 (CAUTION!)..." << endl;
	// Associa cada delivery com o seu respectivo backpoint.
	// OBS: Notei um bug nessa expresssão. Qualquer coisa fazer a adição manual sem um laço (exemplo abaixo)
	for (int d = nTasks; d < nTasks + nStarts; d++) {
		for (int k = 0; k < nRobots; k++) {
			for (int i = nPickTasks; i < nTasks; i++) {
				for (int j = nTasks + nStarts; j < nTasks + nStarts + nBacks; j++) {
					if (nTasks + nStarts + i - nPickTasks != j)
						model.add(x[i][j][k][d - nTasks] == 0);
				}
			}
		}
	}

	if (print_solution) cout << "Expression 21 (CAUTION!)..." << endl;
	// Associa cada delivery com o seu respectivo backpoint.
	/*for (int d = nTasks; d < nTasks + nStarts; d++) {
		for (int k = 0; k < nRobots; k++) {
			model.add(x[10][14][k][d - nTasks] == 0);
			model.add(x[11][13][k][d - nTasks] == 0);
			/*model.add(x[50][57][k][d - nTasks] == 0);
			model.add(x[50][58][k][d - nTasks] == 0);
			model.add(x[50][59][k][d - nTasks] == 0);
			model.add(x[51][56][k][d - nTasks] == 0);
			model.add(x[51][58][k][d - nTasks] == 0);
			model.add(x[51][59][k][d - nTasks] == 0);
			model.add(x[52][56][k][d - nTasks] == 0);
			model.add(x[52][57][k][d - nTasks] == 0);
			model.add(x[52][59][k][d - nTasks] == 0);
			model.add(x[53][56][k][d - nTasks] == 0);
			model.add(x[53][57][k][d - nTasks] == 0);
			model.add(x[53][58][k][d - nTasks] == 0);*/
		/*}
	}*/

	if (print_solution) cout << "Defining Min Formula..." << endl;
	IloExpr cost(env);
	for (int d = nTasks; d < nTasks + nStarts; d++) {
		for (int k = 0; k < nRobots; k++) {
			for (int i = 0; i < nTasks + nStarts + nBacks; i++) {
				for (int j = 0; j < nTasks; j++) {
					cost += (distance_of(i, j) / robots[k].traffic_speed + nodes[j].height / robots[k].lifting_speed) * x[i][j][k][d - nTasks];
				}
			}
		}
	}

	model.add(IloMinimize(env, cost));
	cost.end();

	cout << "Running..." << endl;
	IloCplex cplex(model);
	if (solve_time) 
		cplex.setParam(IloCplex::TiLim, solve_time);
	cplex.solve();
	cout << "Min=" << cplex.getObjValue() << endl;

	if (print_solution) {
		IloNumArray vals(env);
		for (int i = 0; i < nTasks + nStarts + nBacks; i++) {
			for (int j = 0; j < nTasks + nStarts + nBacks; j++) {
				for (int k = 0; k < nRobots; k++) {
					cplex.getValues(vals, x[i][j][k]);
					env.out() << "Values [" << i << "]" << "[" << j << "]" << "[" << k << "] =" << vals << endl;
				}
			}
			env.out() << endl;
		}
	}

	env.end();

	return EXIT_SUCCESS;
}