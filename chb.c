
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
	/*
	printf("total_cnt=%d\n", total_cnt);
	for (int j=1; j<=33; j++){
		printf("ball%-2d ", j);
		for(int i=0; i<7; i++){
			printf("pos%-2d:%-6d ", i+1, position_cnt[j][i]);
		}
		printf("\n");
	}
	*/
	printf("\n\n");

	for (int j=1; j<=33; j++){
		printf("ball%-2d ", j);
		for (int i=0; i<7; i++){
			position_probability[j][i] = (float)position_cnt[j][i] / total_cnt;
			printf("pos%-2d:%-6f ", i+1, position_probability[j][i]);
		}
		printf("\n");
	}

	//predict
	int predict_count = 0;
	fp = fopen("predict_result.txt", "w");
	for (int pos1=1; pos1<=33; pos1++){
		if (position_probability[pos1][0] <= 0.12) continue;
		for (int pos2=1; pos2<=33; pos2++){
			if (pos2 <= pos1) continue; 
			if (position_probability[pos2][1] <= 0.07) continue;
			for (int pos3=1; pos3<=33; pos3++){
				if (pos3 <= pos2) continue;
				if (position_probability[pos3][2] <= 0.063) continue;
				for (int pos4=1; pos4<=33; pos4++){
					if (pos4 <= pos3) continue;
					if (position_probability[pos4][3] <= 0.064) continue;
					for (int pos5=1; pos5<=33; pos5++){
						if (pos5 <= pos4) continue;
						if (position_probability[pos5][4] <= 0.078) continue;
						for (int pos6=1; pos6<=33; pos6++){
							if (pos6 <= pos5) continue;
							if (position_probability[pos6][5] <= 0.10) continue;
							for (int pos7=1; pos7<=16; pos7++){
								if (position_probability[pos7][6] <= 0.064) continue;
								predict_count++;
								fprintf(fp, "%d %d %d %d %d %d %d\n", pos1, pos2, pos3, pos4, pos5, pos6, pos7);
							}
						}
					}
				}
			}
		}
	}
	fclose(fp);
	printf("total situation: %d, you need cost %d RMB.\n",predict_count, predict_count*2);
}
