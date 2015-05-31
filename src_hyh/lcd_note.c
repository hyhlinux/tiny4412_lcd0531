
write_word(unsigned char c)
{


	int i,j;

	u16 cchar;
	if(c == '\n'){
		y += FONT_RAW;
		if(y > 479 - FONT_RAW){
			y = 0;
			clean_lcd(BACK_COL);
		}
		return;
	}

	if(c == '\r'){
		x = 0;
		return;

	}
#ifdef FONT12_22
	const unsigned char *p = &fontdata_sun12x22[c*22*2]; 
#else
	const unsigned char *p = &fontdata_10x18[c*18*2];
#endif 	

	for(i = 0; i < FONT_RAW; i++){
		cchar = (p[2*i] << 8) | p[2*i+1];	 
		for(j = 0; j < FONT_COL; j++){ 
			if(0x8000&(cchar << j)){  
/*
				   cchar = 0x1000
				   0x8000 & (cchar << j) 鎵惧埌涓?鐨勪綅缃?鏄剧ず
*/
				draw_point_char(x+j, y+i, WORD_COL);
			}		
		}
	}

	x += FONT_COL;
	if(x > 799 - FONT_COL){
		x = 0;
		y += FONT_RAW;
		if(y > 479 - FONT_RAW){
			y = 0;
			clean_lcd(BACK_COL);
		}
	}
}

//鍦ㄦ寚瀹氫綅缃啓  ascii

void write_word_pos(unsigned char c, int *pos_x, int *pos_y)
{

	int i,j;
	u16 cchar;
	if(c == '\n'){
		*pos_y += FONT_RAW;
		if(*pos_y > 479 - FONT_RAW){
			*pos_y = 0;
			clean_lcd(BACK_COL);
		}
		return;
	}

	if(c == '\r'){
		*pos_x = 0;
		return;
	}

	//check pos  x [0-799] y [0-479]
	if(*pos_x > 799 - FONT_COL){
		*pos_x = 0;
		*pos_y += FONT_RAW;
		if(*pos_y > 479 - FONT_RAW){
			*pos_y = 0;
			clean_lcd(BACK_COL);
		}
	}

#ifdef FONT12_22
	const unsigned char *p = &fontdata_sun12x22[c*22*2]; 
#else
	const unsigned char *p = &fontdata_10x18[c*18*2];
#endif 	

	for(i = 0; i < FONT_RAW; i++){
		cchar = (p[2*i] << 8) | p[2*i+1];	 
		for(j = 0; j < FONT_COL; j++){ 
			if(0x8000&(cchar << j)){  
				draw_point_char(*pos_x+j, *pos_y+i, WORD_COL);
			}		
		}
	}
	//	x += FONT_COL;
}
/*****************************************

func_name : write_string 
arg		  : char *str, like as "hello world"
		i,j is positions in screen [800*480]
dscription: 
	display a string in screen, start (i,j)
	x=i y=j;
note	  :
	x += FONT_COL;
	j += FONT_RAW;
when you call write_string ,you must know 
where you position and you can call 
clean_lcd(BACK_COL) first;

娉ㄦ剰鏄剧ず2涓浉閭诲瓧绗︽椂,璁＄畻闂磋窛,浠ュ厤浜掔浉瑕嗙洊
x,y = x+FONT_COL , y = y+FONT_RAW	
 *****************************************/
void write_string(char *str,int i, int j)
{

	char *tmp = str;
	for (; *tmp != '\0'; tmp++,i+=FONT_COL) {
		//		printf("*tmp = %c i=%d j=%d\n",*tmp, i, j);
		if (i > 800) {
			i -= 800;
			j+=FONT_RAW;
		}
		if (*tmp == '\n') {
			i = 0;
			j+=FONT_RAW;
			write_word_pos(*tmp, &i, &j);
			tmp++;
		}
		write_word_pos(*tmp, &i, &j);
	}
}
