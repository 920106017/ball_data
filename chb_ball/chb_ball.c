
#include <stdio.h>
void main()
{
	FILE *fp = fopen("./data.txt", "r");
	char str[50]={0};
	int  number[7]={0};

	int position_cnt[34][7]={0};
	memset(position_cnt, 0, sizeof(position_cnt));

	float position_probability[34][7]={0};
	memset(position_probability, 0, sizeof(position_probability));

	int total_cnt = 0;

	while (1){
		if(fgets( str, sizeof(str), fp ) == NULL){
			break;
		}
		//process every ball
		sscanf( str , "%*[^ ] %d %d %d %d %d %d %d", &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6]);
		//printf("parsed: %d %d %d %d %d %d %d\n", number[0], number[1], number[2], number[3], number[4], number[5], number[6]);

		for (int i=0; i<7; i++){
			position_cnt[number[i]][i] += 1;
		}	
		
		total_cnt += 1;			
	}
	
	fclose(fp);

	printf("total_cnt=%d\n", total_cnt);
	for (int j=1; j<=33; j++){
		printf("ball%-2d ", j);
		for(int i=0; i<7; i++){
			printf("pos%-2d:%-6d ", i+1, position_cnt[j][i]);
		}
		printf("\n");
	}
		
	printf("\n\n");

	for (int j=1; j<=33; j++){
		printf("ball%-2d ", j);
		for (int i=0; i<7; i++){
			position_probability[j][i] = (float)position_cnt[j][i] / total_cnt;
			printf("pos%-2d:%-6f ", i+1, position_probability[j][i]);
		}
		printf("\n");
	}




	float probability_sum_min = 1.0;
	float probability_sum_max = 0.0;
	float probability_sum_array[3000] = {0.0}; //3000 line data
	total_cnt = 0;

	fp = fopen("./data.txt", "r");
        while (1){
                if(fgets( str, sizeof(str), fp ) == NULL){
                        break;
                }
                sscanf( str , "%*[^ ] %d %d %d %d %d %d %d", &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6]);
              	float probability_sum = 0.0;
		for (int i=0; i<7; i++){
                	probability_sum += position_probability[number[i]][i];
                }
		if (probability_sum > probability_sum_max){
                	probability_sum_max = probability_sum;
                }
                if (probability_sum < probability_sum_min){
                	probability_sum_min = probability_sum;
                }
		probability_sum_array[total_cnt] = probability_sum;
		total_cnt += 1;
		//printf("%2d %2d %2d %2d %2d %2d %2d ", number[0], number[1], number[2], number[3], number[4], number[5], number[6]);
		//printf("line%4d-probality_sum=%f\n", total_cnt, probability_sum);
		printf("%f\n", probability_sum);

        }

	printf("probability_sum range: %f - %f\n", probability_sum_min, probability_sum_max);
        fclose(fp);
		
	int i = 0;
	int range_cal[10]; //[0.0-0.1) ...
	while(probability_sum_array[i]>0.0){
		if ((probability_sum_array[i]>0.0) && (probability_sum_array[i]<0.1) ){
			range_cal[0] += 1;
		}else if ((probability_sum_array[i]>=0.1) && (probability_sum_array[i]<0.2) ){
                        range_cal[1] += 1;
                }else if ((probability_sum_array[i]>=0.2) && (probability_sum_array[i]<0.3) ){
                        range_cal[2] += 1;
                }else if ((probability_sum_array[i]>=0.3) && (probability_sum_array[i]<0.4) ){
                        range_cal[3] += 1;
                }else if ((probability_sum_array[i]>=0.4) && (probability_sum_array[i]<0.5) ){
                        range_cal[4] += 1;
                }else if ((probability_sum_array[i]>=0.5) && (probability_sum_array[i]<0.6) ){
                        range_cal[5] += 1;
                }else if ((probability_sum_array[i]>=0.6) && (probability_sum_array[i]<0.7) ){
                        range_cal[6] += 1;
                }else if ((probability_sum_array[i]>=0.7) && (probability_sum_array[i]<0.8) ){
                        range_cal[7] += 1;
                }else if ((probability_sum_array[i]>=0.8) && (probability_sum_array[i]<0.9) ){
                        range_cal[8] += 1;
                }else if ((probability_sum_array[i]>=0.9) && (probability_sum_array[i]<1.0) ){
                        range_cal[9] += 1;
                }
		i++;
	}
	printf("probability_sum range(0.0-0.1): has %d line\n", range_cal[0]);
	printf("probability_sum range(0.1-0.2): has %d line\n", range_cal[1]);
	printf("probability_sum range(0.2-0.3): has %d line\n", range_cal[2]);
	printf("probability_sum range(0.3-0.4): has %d line\n", range_cal[3]);
	printf("probability_sum range(0.4-0.5): has %d line\n", range_cal[4]);
	printf("probability_sum range(0.5-0.6): has %d line\n", range_cal[5]);
	printf("probability_sum range(0.6-0.7): has %d line\n", range_cal[6]);
	printf("probability_sum range(0.7-0.8): has %d line\n", range_cal[7]);
	printf("probability_sum range(0.8-0.9): has %d line\n", range_cal[8]);
	printf("probability_sum range(0.9-1.0): has %d line\n", range_cal[9]);


	//predict
	int predict_count = 0;
	fp = fopen("predict_result.txt", "w");
	for (int pos1=1; pos1<=33; pos1++){
		printf("first ball has predicted to %d\n", pos1);
		if (position_probability[pos1][0] <= 0.0) continue;
		for (int pos2=1; pos2<=33; pos2++){
			if (pos2 <= pos1) continue; 
			if (position_probability[pos2][1] <= 0.0) continue;
			for (int pos3=1; pos3<=33; pos3++){
				if (pos3 <= pos2) continue;
				if (position_probability[pos3][2] <= 0.0) continue;
				for (int pos4=1; pos4<=33; pos4++){
					if (pos4 <= pos3) continue;
					if (position_probability[pos4][3] <= 0.0) continue;
					for (int pos5=1; pos5<=33; pos5++){
						if (pos5 <= pos4) continue;
						if (position_probability[pos5][4] <= 0.0) continue;
						for (int pos6=1; pos6<=33; pos6++){
							if (pos6 <= pos5) continue;
							if (position_probability[pos6][5] <= 0.0) continue;
							for (int pos7=1; pos7<=16; pos7++){
								if (position_probability[pos7][6] <= 0.0) continue;
								float probbty_sum = position_probability[pos1][0] +
										position_probability[pos2][1]+
										position_probability[pos3][2]+
										position_probability[pos4][3]+
										position_probability[pos5][4]+
										position_probability[pos6][5]+
										position_probability[pos7][6];
								if ((probbty_sum >= 0.3) && (probbty_sum <= 0.7)){
									predict_count++;
									fprintf(fp, "%2d %2d %2d %2d %2d %2d %2d\n", pos1, pos2, pos3, pos4, pos5, pos6, pos7);
								}
							}
						}
					}
				}
			}
		}
	}
	fclose(fp);
}
