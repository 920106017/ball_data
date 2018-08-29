#include <stdio.h>

#define X_NUM 1
#define X_MAX_TYPE_NUM 25
#define Y_MAX_TYPE_NUM 33

char *X_TABLE[X_NUM][X_MAX_TYPE_NUM] = {
{"YEAR0", "YEAR1", "YEAR2", "YEAR3", "YEAR4", "YEAR5", "YEAR6", "YEAR7", "YEAR8", "YEAR9", "YEAR10", "YEAR11", "YEAR12", "YEAR13", "YEAR14", "YEAR15", "YEAR16", "YEAR17", "YEAR18", "YEAR19", "YEAR20", "YEAR21", "YEAR22", "YEAR23", "YEAR24", },
};

char *Y_TABLE[Y_MAX_TYPE_NUM] = {"R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15", "R16", "R17", "R18", "R19", "R20", "R21", "R22", "R23", "R24", "R25", "R26", "R27", "R28", "R29", "R30", "R31", "R32", "R33"};

typedef struct{
	unsigned long count_array[X_NUM][X_MAX_TYPE_NUM][Y_MAX_TYPE_NUM];
	unsigned long sum_count_array[X_NUM][X_MAX_TYPE_NUM];
	float rate_array[X_NUM][X_MAX_TYPE_NUM][Y_MAX_TYPE_NUM];
}data_info_t;

data_info_t g_data_info;

void main(void)
{
	FILE *fp = fopen("data.txt", "r");
	if (!fp){
		printf("open data.txt fail\n");
		return;
	}
	
	int x_num_index = 0;
	int x_max_type_index = 0;
	int y_num_index = 0;
	//modify here ，10列表示这个table标签字符串的长度不能超过9， ‘\0’ 占用一个字节
	char temp_data[X_NUM + 1][10]; //"输入条件1的类型字符串"
								  //"输入条件2的类型字符串"
								  //"输入条件3的类型字符串"
								  // ...
								  //"输出结果的类型字符串"
	char str[50];
	int  number[7];
	int total = 0;
	memset(&g_data_info, 0, sizeof(g_data_info));
	while (1){
		if(fgets( str, sizeof(str), fp ) == NULL){
			break;
		}
		total++;
		sscanf( str , "%*[^ ] %d %d %d %d %d %d %d", &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6]);
		//现在
		strcpy(temp_data[0], X_TABLE[0][total % X_MAX_TYPE_NUM]);
		sprintf(temp_data[1], "R%d", number[4]);
		x_num_index = 0;
		x_max_type_index = 0;
		y_num_index = 0;
		for (x_num_index = 0; x_num_index < X_NUM; x_num_index++){
			for (x_max_type_index = 0; x_max_type_index < X_MAX_TYPE_NUM; x_max_type_index++){
				if (strcmp(X_TABLE[x_num_index][x_max_type_index], temp_data[x_num_index]) == 0){
					g_data_info.sum_count_array[x_num_index][x_max_type_index]++;
					for (y_num_index = 0; y_num_index < Y_MAX_TYPE_NUM; y_num_index++){
						if (strcmp(Y_TABLE[y_num_index], temp_data[X_NUM]) == 0){
							g_data_info.count_array[x_num_index][x_max_type_index][y_num_index]++;
						}
					}
				}
			} 
		}
	}
	
	fclose(fp);
#if 1
	//show count
	for (x_num_index = 0; x_num_index < X_NUM; x_num_index++){
			for (x_max_type_index = 0; x_max_type_index < X_MAX_TYPE_NUM; x_max_type_index++){
					for (y_num_index = 0; y_num_index < Y_MAX_TYPE_NUM; y_num_index++){
							printf(" x%d -> type%d == y%d has %lu count\n", x_num_index, x_max_type_index, y_num_index, g_data_info.count_array[x_num_index][x_max_type_index][y_num_index]);
					}
			} 
	}
	
	//calculate
	for (x_num_index = 0; x_num_index < X_NUM; x_num_index++){
		for (x_max_type_index = 0; x_max_type_index < X_MAX_TYPE_NUM; x_max_type_index++){
			for (y_num_index = 0; y_num_index < Y_MAX_TYPE_NUM; y_num_index++){
				if (g_data_info.sum_count_array[x_num_index][x_max_type_index] == 0){
					g_data_info.rate_array[x_num_index][x_max_type_index][y_num_index] = 0.0;
				}else{
					g_data_info.rate_array[x_num_index][x_max_type_index][y_num_index] = (float)((double)g_data_info.count_array[x_num_index][x_max_type_index][y_num_index] / g_data_info.sum_count_array[x_num_index][x_max_type_index]);
				}
			} 
		}
	}
	
	//show rate
	for (x_num_index = 0; x_num_index < X_NUM; x_num_index++){
			for (x_max_type_index = 0; x_max_type_index < X_MAX_TYPE_NUM; x_max_type_index++){
					//sort, sort rate , but save y_num_index
					int sort_max_to_min[Y_MAX_TYPE_NUM] = {0};
					float max_rate = 0.0;
					int i,j;
					for (j = 0; j < Y_MAX_TYPE_NUM; j++){
						max_rate = 0.0;
						for (i = 0; i < Y_MAX_TYPE_NUM; i++){
							if (g_data_info.rate_array[x_num_index][x_max_type_index][i] >= max_rate){
								int k = 0;
								int find = 0;
								for(k = 0; k < j; k++){
									if (sort_max_to_min[k] == i){
										find = 1; //mark it has been handle before.
									}
								}
								if (!find){
									sort_max_to_min[j] = i;
									max_rate = g_data_info.rate_array[x_num_index][x_max_type_index][i];
								} 
							}
						}
					}
					for (i = 0; i < Y_MAX_TYPE_NUM; i++){
							printf(" x%d -> %s == %s rate:%f\n", x_num_index, X_TABLE[x_num_index][x_max_type_index], Y_TABLE[sort_max_to_min[i]], g_data_info.rate_array[x_num_index][x_max_type_index][sort_max_to_min[i]] );
					}
			} 
	}
	
	printf("total sample count: %d\n", total);
#endif
}























