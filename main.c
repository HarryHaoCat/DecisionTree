/*************************************************************************
	> File Name: main.c
	> Author: HarryHao
	> Mail: 95448758@qq.com 
	> Created Time: 2018年07月11日 星期三 10时47分49秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
int main()
{
 TRAINING trainingSet[TRAINING_NUMBER] =
{
{ SUNNY   , HIGH_TEMPERATURE, HIGH_HUMIDITY,   NO_WIND, NOT_PLAY, NULL },
{ SUNNY   , HIGH_TEMPERATURE, HIGH_HUMIDITY,   WIND ,   NOT_PLAY, NULL },
{ VOERCAST, HIGH_TEMPERATURE, HIGH_HUMIDITY,   NO_WIND, CAN_PLAY, NULL },
{ RAIN    , MID_TEMPERATURE,  HIGH_HUMIDITY,   NO_WIND, CAN_PLAY, NULL },
{ RAIN    , COLD_TEMPERATURE, NORMAL_HUMIDITY, NO_WIND, CAN_PLAY, NULL },
{ RAIN    , COLD_TEMPERATURE, NORMAL_HUMIDITY, WIND ,   NOT_PLAY, NULL },
{ VOERCAST, COLD_TEMPERATURE, NORMAL_HUMIDITY, WIND ,   CAN_PLAY, NULL },
{ SUNNY   , MID_TEMPERATURE,  HIGH_HUMIDITY,   NO_WIND, NOT_PLAY, NULL },
{ SUNNY   , COLD_TEMPERATURE, NORMAL_HUMIDITY, NO_WIND, CAN_PLAY, NULL },
{ RAIN    , MID_TEMPERATURE,  NORMAL_HUMIDITY, NO_WIND, CAN_PLAY, NULL },
{ SUNNY   , MID_TEMPERATURE,  NORMAL_HUMIDITY, WIND ,   CAN_PLAY, NULL },
{ VOERCAST, MID_TEMPERATURE,  HIGH_HUMIDITY,   WIND ,   CAN_PLAY, NULL },
{ VOERCAST, HIGH_TEMPERATURE, NORMAL_HUMIDITY, NO_WIND, CAN_PLAY, NULL },
{ RAIN    , MID_TEMPERATURE,  HIGH_HUMIDITY,   WIND ,   NOT_PLAY, NULL }
};
 TRAINING* head =  trainingInit(trainingSet);
 TREE* t = (TREE*)malloc(sizeof(TREENODE));
 createTree(t, head);
 for(int i = 0; i < 14; i++)
 {
     printf("%s\n", classify(t, head)-14?"NOT_PLAY":"CAN_PLAY");
     head = head->next;
 }//TRAINING* sub = splitData(TEMPERATURE,HIGH_TEMPERATURE, head);
 //sub = splitData(OUTLOOK,SUNNY, sub); 
 //double a = calEntropy(head);
 //printf("信息熵为%f\n", a);
 //printf("最好的划分为%d\n", choseBestFeature(sub));

 return 0;
}

