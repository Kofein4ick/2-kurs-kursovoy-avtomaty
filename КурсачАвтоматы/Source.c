#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	FILE* IN;//указатель на входной файл
	FILE* OUT;//указатель на вспомогательный файл
	short bw;//координата начала слова
	short ew;//координата конца слова
	short countword = 0;//счетчик слов
	short bw_temp;//координата начала слова для запоминания
	short ew_temp;//координата конца слова для запоминания
	short counttemp = 0;//счетчик р/ых импликант
	short countallword = 1;//счетчик всех слов
	short countstring = 1;//счетчи
	//массивы для строк
	char Str[1024];
	char Str2[1024];
	char** Matrix;//массив для импликантной матрицы
	short lentghstr;//длина строки
	short lentghword;//длина слова
	short templentghstr;//переменная для сохранения длины строки
	//флаги
	short y = 0xFF;
	short flag = 0;
	short flagx = 0;
	short count = 0;
	short flags = 0;
	//переменные
	short i = 0;
	short j = 0;
	short a = 0;
	short q = 0;
	short k = 1;
	short temp = 0;//переменная для сохранения
	IN = fopen("Text.txt", "rt");//входной файл
	if (IN == NULL)
	{
		printf("Ошибка! Не удалось открыть входной файл.");
		getchar();
		return 1;
	}
	OUT = fopen("Out.txt", "wt+");//вспомогательный файл
	if (OUT == NULL)
	{
		printf("Ошибка! Не удалось открыть вспомогательный файл.");
		getchar();
		fclose(IN);
		return 2;
	}
	memset(Str, 0, sizeof(Str));
	fgets(Str, 500, IN);//чтение строки
	printf("Введенная ДНФ:\n%s\n", Str);
	fputs(Str, OUT);
	lentghstr = strlen(Str);
	templentghstr=lentghstr;

	//Операция общего склеивания
	while (i < lentghstr)
	{
		//выбор импликанты(сохранение)
		if (flag == 0)
		{
			while ((ispunct(Str[i])) || (isspace(Str[i])))
				i++;
			if (Str[i] == '\0')
				break;
			bw_temp = i;
			ew_temp = bw_temp;
			while (!(ispunct(Str[i])) && !(isspace(Str[i])) && (i < lentghstr))
			{
				ew_temp++;
				i++;
			}
			ew_temp--;
			lentghword = ew_temp - bw_temp + 1;
			counttemp++;
			flag = 1;
		}
		//выбор следующей импликанты и сравнение с сохраненной
		while ((ispunct(Str[i])) || (isspace(Str[i])))
			i++;
		bw = i;
		ew = bw;
		while (!(ispunct(Str[i])) && !(isspace(Str[i])) && (i < lentghstr))
		{
			ew++;
			i++;
		}
		ew--;
		if (flags == 0)
			countallword++;
		if (lentghword == (ew - bw + 1))
		{
			for (j = 0; j < lentghword; j++)
				if ((Str[bw + j] == Str[bw_temp + j])||(Str[bw_temp+j]=='x'))
					count++;
			if (count == lentghword - 1)
			{
				fputc('+', OUT);
				for (j = 0; j < lentghword; j++)
				{
					if ((Str[bw + j] == Str[bw_temp + j]))
						fputc(Str[bw + j], OUT);
						else
							fputc('x', OUT);
				}
			}
			count = 0;
			i++;
			//вовзрат в начало строки и сохранение следующей импликанты
			if ((i >= lentghstr) && (counttemp < countallword))
			{
				i = ew_temp + 1;
				flag = 0;
				flags = 1;
			}
		}
	}
	temp = countallword;//сохранение исходного кол-ва импликант
	counttemp = 0;
	countallword = 1;
	flag = 0;
	flags = 0;
	count = 0;
	rewind(OUT);
	memset(Str, 0, sizeof(Str));
	//операция общего склеивания с учетом полученных дизъюнктов
	while (fgets(Str, 500, OUT) != NULL)
	{
		lentghstr = strlen(Str);
		while (i < lentghstr)
		{
			if (flag == 0)
			{
				while ((ispunct(Str[i])) || (isspace(Str[i])))
					i++;
				if (Str[i] == '\0')
					break;
				bw_temp = i;
				ew_temp = bw_temp;
				while (!(ispunct(Str[i])) && !(isspace(Str[i])) && (i < lentghstr))
				{
					ew_temp++;
					i++;
				}
				ew_temp--;
				lentghword = ew_temp - bw_temp + 1;
				counttemp++;
				flag = 1;
			}
			while ((ispunct(Str[i])) || (isspace(Str[i])))
				i++;
			bw = i;
			ew = bw;
			while (!(ispunct(Str[i])) && !(isspace(Str[i])) && (i < lentghstr))
			{
				ew++;
				i++;
			}
			ew--;
			if (flags == 0)
				countallword++;
			if (lentghword == (ew - bw + 1))
			{
				for (j = 0; j < lentghword; j++)
					if ((Str[bw + j] == Str[bw_temp + j]))
						count++;
				if (count == lentghword - 1)
				{
					fputc('+', OUT);
					for (j = 0; j < lentghword; j++)
					{
						if ((Str[bw + j] == Str[bw_temp + j]))
							fputc(Str[bw + j], OUT);
						else
								fputc('x', OUT);
					}
					flagx = 1;
				}
			}
			count = 0;
			i++;
			if ((i >= lentghstr) && (counttemp < countallword))
			{
				i = ew_temp + 1;
				flag = 0;
				flags = 1;
			}
		}//если была склейка и расммотрены все импликанты
		if ((counttemp >= countallword) && (flagx == 1))
		{
			rewind(OUT);
			flagx = 0;
			flags = 0;
			flag = 0;
			counttemp = 0;
			countallword = 1;
			k = 1;
		}
		memset(Str, 0, sizeof(Str));
	}
	rewind(OUT);

	//Операция поглощения
	fgets(Str, 500, OUT);
	i = templentghstr + 1;
	flag = 0;
	count = 0;
	while (i < lentghstr)
	{
		//сохранение импликанты
		if (flag == 0)
		{
			while ((ispunct(Str[i])) || (isspace(Str[i])))
				i++;
			if (Str[i] == '\0')
				break;
			bw_temp = i;
			ew_temp = bw_temp;
			while (!(ispunct(Str[i])) && !(isspace(Str[i])) && (i < lentghstr))
			{
				ew_temp++;
				i++;
			}
			ew_temp--;
			lentghword = ew_temp - bw_temp + 1;
			flag = 1;
			i = 0;
		}
		//выбор импликант
		while ((ispunct(Str[i])) || (isspace(Str[i])))
			i++;
		bw = i;
		ew = bw;
		while (!(ispunct(Str[i])) && !(isspace(Str[i])) && (i < lentghstr))
		{
			ew++;
			i++;
		}
		ew--;
		//поглощение
		if (lentghword == (ew - bw + 1))
		{
			for (j = 0; j < lentghword; j++)
				if ((Str[bw + j] == Str[bw_temp + j]) || (Str[bw_temp + j] == 'x'))
					count++;
			if (count == lentghword)
			{
				for (int q = 0; q < lentghword + 1; q++)
				{
					for (j = bw; j < lentghstr; j++)
						Str[j] = Str[j + 1];
					lentghstr = strlen(Str);
				}
				i = i - (lentghword + 1);
				bw_temp = bw_temp - (lentghword + 1);
				ew_temp = ew_temp - (lentghword + 1);
			}
		}
		count = 0;
		i++;
		if (i == bw_temp)
		{
			i = ew_temp + 1;
			flag = 0;
		}
	}
	i = 0;
	counttemp = 0;
	//определение кол-ва полученных простых импликант
	while (i < strlen(Str))
	{
		while ((ispunct(Str[i])) || (isspace(Str[i])))
			i++;
		while (!(ispunct(Str[i])) && !(isspace(Str[i])) && (i < lentghstr))
			i++;
		counttemp++;
	}
	printf("Полученная СокрДНФ:\n%s", Str);
	memset(Str2, 0, sizeof(Str2));
	rewind(IN);
	fclose(OUT);
	OUT = fopen("Out.txt", "wt");
	fgets(Str2, 500, IN);
	count = 0;
	countallword = temp;
	Matrix = (char**)malloc(countallword * sizeof(char*));
	for (i = 0; i < countallword; i++)
	{
		Matrix[i] = (char*)malloc(counttemp * sizeof(char));
		memset(Matrix[i], 0, counttemp * sizeof(char) + 4);
	}
	countstring = counttemp;
	i = 0;
	j = 0;
	counttemp = -1;
	countallword = -1;

	//Заполнение импликантной матрицы
	while (i < strlen(Str2))
	{
		//выбор импликанты
		while ((ispunct(Str2[i])) || (isspace(Str2[i])))
			i++;
		if (Str2[i] == '\0')
			break;
		bw_temp = i;
		ew_temp = bw_temp;
		while (!(ispunct(Str2[i])) && !(isspace(Str2[i])) && (i < strlen(Str2)))
		{
			ew_temp++;
			i++;
		}
		ew_temp--;
		lentghword = ew_temp - bw_temp + 1;
		countallword++;
		while (j < strlen(Str))
		{
			//выбор простой импликанты
			while ((ispunct(Str[j])) || (isspace(Str[j])))
				j++;
			bw = j;
			ew = bw;
			while (!(ispunct(Str[j])) && !(isspace(Str[j])) && (j < strlen(Str)))
			{
				ew++;
				j++;
			}
			ew--;
			counttemp++;
			//заполнение матрицы
			if (lentghword == (ew - bw + 1))
			{
				for (short q = 0; q < lentghword; q++)
					if ((Str[bw + q] == Str2[bw_temp + q]) || (Str[bw + q] == 'x'))
						count++;
				if (count == lentghword)
				{
					Matrix[countallword][counttemp] = '*';
				}
			}
			count = 0;
		}
		counttemp = -1;
		j = 0;
	}
	for (i = 0; i < countallword + 1; i++)
	{
		for (j = 0; j < countstring; j++)
		{
			if (Matrix[i][j] == '*')
			{
				count++;
				temp = j;
			}
		}
		//поиск уникальных покрытий
		if (count == 1)
		{//вычеркивание всех импликант, которые покрываются текущей простой импликантой
			for (q = 0; q < countallword + 1; q++)
			{
				if (Matrix[q][temp] == '*')
					for (a = 0; a < countstring; a++)
						Matrix[q][a] = '+';
			}
			q = 0;
			while (q < strlen(Str))
			{
				while ((ispunct(Str[q])) || (isspace(Str[q])))
					q++;
				bw = q;
				ew = bw;
				while (!(ispunct(Str[q])) && !(isspace(Str[q])) && (q < strlen(Str)))
				{
					ew++;
					q++;
				}
				ew--;
				countword++;
				//печать простой импликанты в массив
				if (countword - 1 == temp)
				{
					for (int b = bw; b < ew + 1; b++)
						fprintf(OUT, "%c", Str[b]);
					fputc('+', OUT);
					break;
				}
			}
			countword = 0;
		}
		count = 0;
	}
	counttemp = 0;
	temp = -1;

	//Добор в случае не полностью покрытой матрицы
	while (temp == -1)
	{//поиск простой импликанты с наибольшим числом покрытий
		for (j = 0; j < countstring; j++)
		{
			for (i = 0; i < countallword + 1; i++)
				if (Matrix[i][j] == '*')
					count++;
			if (counttemp < count)
			{
				counttemp = count;
				temp = j;
			}
			count = 0;
		}
		if (temp != -1)
		{//вычеркивание всех импликант,которые покрываются текущей простой импликантой
			for (q = 0; q < countallword + 1; q++)
			{
				if (Matrix[q][temp] == '*')
					for (a = 0; a < countstring; a++)
						Matrix[q][a] = '+';
			}
			q = 0;
			while (q < strlen(Str))
			{
				while ((ispunct(Str[q])) || (isspace(Str[q])))
					q++;
				bw = q;
				ew = bw;
				while (!(ispunct(Str[q])) && !(isspace(Str[q])) && (q < strlen(Str)))
				{
					ew++;
					q++;
				}
				ew--;
				countword++;
				//печать простой импликанты в массив
				if (countword - 1 == temp)
				{
					for (int b = bw; b < ew + 1; b++)
						fprintf(OUT, "%c", Str[b]);
					fputc('+', OUT);
					counttemp = 0;
					break;
				}
			}
			countword = 0;
		}
		else
			break;
		temp = -1;
	}
	rewind(OUT);
	fclose(OUT);
	OUT = fopen("Out.txt", "rt");
	memset(Str, 0, sizeof(Str));
	fgets(Str, 500, OUT);
	i = 0;
	counttemp = 0;
	countallword = 1;
	count = 0;
	flags = 0;
	flag = 0;

	//Удаление повторяющихся простых импликант
	while (i < strlen(Str))
	{
		if (flag == 0)
		{
			while ((ispunct(Str[i])) || (isspace(Str[i])))
				i++;
			if (Str[i] == '\0')
				break;
			bw_temp = i;
			ew_temp = bw_temp;
			while (!(ispunct(Str[i])) && !(isspace(Str[i])) && (i < strlen(Str)))
			{
				ew_temp++;
				i++;
			}
			ew_temp--;
			lentghword = ew_temp - bw_temp + 1;
			counttemp++;
			flag = 1;
		}
		while ((ispunct(Str[i])) || (isspace(Str[i])))
			i++;
		bw = i;
		ew = bw;
		while (!(ispunct(Str[i])) && !(isspace(Str[i])) && (i < strlen(Str)))
		{
			ew++;
			i++;
		}
		ew--;
		if (flags == 0)
			countallword++;
		if (lentghword == (ew - bw + 1))
		{
			for (j = 0; j < lentghword; j++)
				if (Str[bw + j] == Str[bw_temp + j])
					count++;
			if (count == lentghword)
			{
				for (int q = 0; q < lentghword + 1; q++)
				{
					for (j = bw; j < strlen(Str); j++)
						Str[j] = Str[j + 1];
				}
				i = i - (lentghword + 1);
				countallword--;
			}
		}
		count = 0;
		i++;
		if ((i >= lentghstr) && (counttemp < countallword))
		{
			i = ew_temp + 1;
			flag = 0;
			flags = 1;
		}
	}
	Str[strlen(Str) - 1] = '\0';
	printf("\nПолученная МДНФ:\n%s", Str);
	getchar();
	return 0;
	
}