/**************************************************
	> File Name: tree.c
	> Author: HarryHao
	> Mail: 954487858@qq.com 
	> Created Time: 2018年07月11日 星期三 10时48分22秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tree.h"

TRAINING* trainingInit(TRAINING trainingSet[])
{
    TRAINING* p = (TRAINING*)malloc(sizeof(TRAINING));
    p->outLook = trainingSet[0].outLook;
    p->temperature = trainingSet[0].temperature;
    p->humidity = trainingSet[0].humidity;
    p->windy = trainingSet[0].windy;
    p->play = trainingSet[0].play;
    TRAINING* head = p;
    for (int i = 1; i < 14; i++)
    {
        p->next = (TRAINING*)malloc(sizeof(TRAINING));
        p = p -> next;
        p->outLook = trainingSet[i].outLook;
        p->temperature = trainingSet[i].temperature;
        p->humidity = trainingSet[i].humidity;
        p->windy = trainingSet[i].windy;
        p->play = trainingSet[i].play;
    }
    return head;
} 

//按照属性值划分数据集
TRAINING* splitData(int feature, int class, TRAINING* head)
{

    TRAINING* p = head;
    TRAINING* subHead = (TRAINING*)malloc(sizeof(TRAINING));
    TRAINING* temp = subHead;
    temp->next = NULL;
    while(p != NULL)
    {
        if(feature == OUTLOOK)
        {
         if(p->outLook == class)
         {
                
            temp->next = (TRAINING*)malloc(sizeof(TRAINING));
            temp = temp->next;
            temp->outLook = NOTHING;
            temp->temperature = p->temperature;
            temp->humidity = p->humidity;
            temp->windy = p->windy;
            temp->play = p->play;
            temp->next = NULL;
         }
         p = p->next;
        }
        else if(feature == TEMPERATURE)
        {
         if(p->temperature == class)
         {
                
            temp->next = (TRAINING*)malloc(sizeof(TRAINING));
            temp = temp->next;
            temp->outLook = p->outLook;
            temp->temperature = NOTHING;
            temp->humidity = p->humidity;
            temp->windy = p->windy;
            temp->play = p->play;
            temp->next = NULL;
         }
         p = p->next;
        }
        else if(feature == HUMIDITY)
        {
         if(p->humidity == class)
         {
                
            temp->next = (TRAINING*)malloc(sizeof(TRAINING));
            temp = temp->next;
            temp->outLook = p->outLook;
            temp->temperature = p->temperature;
            temp->humidity = NOTHING;
            temp->windy = p->windy;
            temp->play = p->play;
            temp->next = NULL;
         }
         p = p->next;
        }    
        else if(feature == WINDY)
        {
         if(p->windy == class)
         {
                
            temp->next = (TRAINING*)malloc(sizeof(TRAINING));
            temp = temp->next;
            temp->outLook = p->outLook;
            temp->temperature = p->temperature;
            temp->humidity = p->humidity;
            temp->windy = NOTHING;
            temp->play = p->play;
            temp->next = NULL;
         }
         p = p->next;

        }
    }
    if(subHead->next)
    {
        subHead = subHead->next;
        return subHead;
    }
    else return NULL;

}


//计算某个划分子集的信息熵
double calEntropy(TRAINING* head)
{
    double num = 0.0;
    double play = 0.0;
    double not_play = 0.0;
    TRAINING* p = head;
    while(p != NULL)
    {
        if(p->play == CAN_PLAY)
        {
            play++;
        }
        else if(p->play == NOT_PLAY) 
            not_play++;
        num++;
        p = p->next;
    }
    //printf("play/num = %f, not_play/num= %f, ", (double)(play/num), (double)(not_play/num));
    //printf("num = %f\n", num);
    return Entropy((double)(play/num), (double)(not_play/num));

}

double log2(double x)
{
    if(x < 0.0)
        return -1.0;
    return (double)log(x)/log(2.0);
}

double Entropy(double p1, double p2)
{
   if(p1 > 0.0 && p2 > 0.0)
   {
        double e = -p1 * log2(p1) - p2 * log2(p2); 
        return e;
   }
   else
        return 0;
}

//计算某个子集的个数
double num(TRAINING* head)
{
    double number = 0.0;
    TRAINING* p = head;
    while(p != NULL)
    {
        p = p->next;
        number++;
    }
    return number;
}

//子集划分结束的标志：如果属于同一类则划分结束，返回类标签
int IsOneClass(TRAINING* head)
{
    TRAINING* p = head;
    if(p->next == NULL)
        return p->play;        //只有一个节点
    else
    {   
        int same = p->play;
        p = p->next;
        while(p)
        {
            if(p->play != same)
                return 0;//出现不一致的类就返回0;
            p = p->next;
        }
        return same;
    }
}
//用完所有的属性依然不属于同一类，则最多的类为类标签
int majorityCnt(TRAINING* head)
{
    int num1, num2 = 0;
    TRAINING* p = head;
    while(p)
    {
        if(p->play == CAN_PLAY) num1++;
        else if(p->play == NOT_PLAY) num2++;
        p = p->next;
    }
    return num1 >= num2?CAN_PLAY:NOT_PLAY;
}

//计算某个属性的信息熵,选取最好的划分属性
int choseBestFeature(TRAINING* p)
{
    double max1 =100.0, max2 = 100.0, max3 = 100.0, max4 = 100.0; 
    if(p->outLook != NOTHING)
    {
        TRAINING* sunny = splitData(OUTLOOK, SUNNY, p);
        TRAINING* rain = splitData(OUTLOOK, RAIN, p);
        TRAINING* voercast = splitData(OUTLOOK, VOERCAST, p);
        double p1 = calEntropy(sunny); 
        double p2 = calEntropy(rain); 
        double p3 = calEntropy(voercast);
        double num1 = num(sunny);
        double num2 = num(rain);
        double num3 = num(voercast);
        max1 = (double)(num1 * p1 + num2 * p2 + num3 * p3)/(num1 + num2 + num3);
    }

    if(p->temperature != NOTHING)
    {
        TRAINING* high_temperature = splitData(TEMPERATURE, HIGH_TEMPERATURE, p);
        TRAINING* mid = splitData(TEMPERATURE, MID_TEMPERATURE, p);
        TRAINING* cold = splitData(TEMPERATURE, COLD_TEMPERATURE, p);
        double p1 = calEntropy(high_temperature);
        double p2 = calEntropy(mid);
        double p3 = calEntropy(cold);
        double num1 = num(high_temperature);
        double num2 = num(mid);
        double num3 = num(cold);
        max2 = (double)(num1 * p1 + num2 * p2 + num3 * p3)/(num1 + num2 + num3);
    }

    if(p->humidity != NOTHING)
    {
        TRAINING* high_hum = splitData(HUMIDITY, HIGH_HUMIDITY, p);
        TRAINING* normal = splitData(HUMIDITY, NORMAL_HUMIDITY, p);
        double p1 = calEntropy(high_hum);
        double p2 = calEntropy(normal);
        double num1 = num(high_hum);
        double num2 = num(normal);
        max3 = (double)(num1 * p1 + num2 * p2)/(num1 + num2);
    }
 
    if(p->windy != NOTHING)
    {
        TRAINING* wind = splitData(WINDY, WIND, p);
        TRAINING* no_wind = splitData(WINDY, NO_WIND, p);
        double p1 = calEntropy(wind);
        double p2 = calEntropy(no_wind);
        double num1 = num(wind);
        double num2 = num(no_wind);
        max4 = (double)(num1 * p1 + num2 * p2)/(num1 + num2);
    }
    //printf("outlook = %f, temp = %f, hum = %f, wind = %f\n",max1,max2,max3,max4);
    double m1 = max1 <= max2? max1:max2;
    double m2 = max3 <= max4? max3:max4;
    double m3 = m1 <= m2? m1:m2;
    if(m3 == m1)
    {
        if(m3 == max1)
            return OUTLOOK;
        else return TEMPERATURE;
    }
    else if(m3 == m2)
    {
        if(m3 == max3)
            return HUMIDITY;
        else return WINDY;
    }

}

//建树函数载入，传入数据集的头指针和指向子节点的指针,递归创建树
void createTree(TREE* tree, TRAINING* head)
{
 if(tree)
 {

    *tree = (TREE*)malloc(sizeof(TREENODE));

    if(IsOneClass(head)) //如果属于一个类就将该节点视为叶子节点
    {
        (*tree)->attribute = IsOneClass(head);
        (*tree)->left = NULL;
        (*tree)->right = NULL;
        (*tree)->mid = NULL;
        return;       
    }
    if(head->outLook == NOTHING && head->temperature == NOTHING && head->humidity == NOTHING && head->windy == NOTHING)
    {
        (*tree)->attribute = majorityCnt(head);
        (*tree)->left = NULL;
        (*tree)->right = NULL;
        (*tree)->mid = NULL;
        return;  
    }
    int bestFeature = choseBestFeature(head);
    //(*tree)->attribute = bestFeature;
    if(bestFeature == OUTLOOK)
    {
        (*tree)->attribute = bestFeature;   
        createTree(&((*tree)->left), splitData(OUTLOOK,SUNNY,head));
        createTree(&((*tree)->right), splitData(OUTLOOK,VOERCAST,head));
        createTree(&((*tree)->mid),splitData(OUTLOOK,RAIN,head));
    }
    if(bestFeature == TEMPERATURE)
    {
        (*tree)->attribute = bestFeature;   
        createTree(&((*tree)->left), splitData(TEMPERATURE,HIGH_TEMPERATURE,head));
        createTree(&((*tree)->right), splitData(TEMPERATURE,MID_TEMPERATURE,head));
        createTree(&((*tree)->mid), splitData(TEMPERATURE,COLD_TEMPERATURE,head));
    }
    if(bestFeature == HUMIDITY)
    {
        (*tree)->attribute = bestFeature;   
        createTree(&((*tree)->left), splitData(HUMIDITY,HIGH_HUMIDITY,head));
        createTree(&((*tree)->right), splitData(HUMIDITY,NORMAL_HUMIDITY,head));
        (*tree)->mid = NULL;
    }
    if(bestFeature == WINDY)
    {
        (*tree)->attribute = bestFeature;   
        createTree(&((*tree)->left), splitData(WINDY,WIND,head));
        createTree(&((*tree)->right), splitData(WINDY,NO_WIND,head));
        (*tree)->mid = NULL;
    }

 }
}

//分类函数
int classify(TREE* tree, TRAINING* head)
<<<<<<< HEAD
{
    if((*tree)->attribute == CAN_PLAY || (*tree)->attribute == NOT_PLAY)
        return (*tree)->attribute;
    else
    {
        int attributes = (*tree)->attribute;
        if(attributes == OUTLOOK)
        {
            switch(head->outLook)       
            {
                case SUNNY: classify(&((*tree)->left), head);
                            break;
                case RAIN:  classify(&((*tree)->mid), head);
                            break;
                case VOERCAST: classify(&((*tree)->right), head);
                            break;
            }
        }
        if(attributes == TEMPERATURE)
        {
            switch(head->humidity)       
            {
                case HIGH_HUMIDITY: classify(&((*tree)->left), head);
                                    break;
                case NORMAL_HUMIDITY: classify(&((*tree)->right), head);
                                    break;
            }
        }
        if(attributes == WINDY)
        {
            switch(head->windy)       
            {
                case WIND: classify(&((*tree)->left), head);
                           break;
                case NO_WIND: classify(&((*tree)->right), head);
                              break;
            }
        }
    }
}


=======
{
    if((*tree)->attribute == CAN_PLAY || (*tree)->attribute == NOT_PLAY)
        return (*tree)->attribute;
    else
    {
        int attributes = (*tree)->attribute;
        if(attributes == OUTLOOK)
        {
            switch(head->outLook)       
            {
                case SUNNY: classify(&((*tree)->left), head);
                            break;
                case RAIN:  classify(&((*tree)->mid), head);
                            break;
                case VOERCAST: classify(&((*tree)->right), head);
                            break;
            }
        }
        if(attributes == TEMPERATURE)
        {
            switch(head->humidity)       
            {
                case HIGH_HUMIDITY: classify(&((*tree)->left), head);
                                    break;
                case NORMAL_HUMIDITY: classify(&((*tree)->right), head);
                                    break;
            }
        }
        if(attributes == WINDY)
        {
            switch(head->windy)       
            {
                case WIND: classify(&((*tree)->left), head);
                           break;
                case NO_WIND: classify(&((*tree)->right), head);
                              break;
            }
        }
    }
}


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

>>>>>>> 42fdf2659efdcb674df64eb7c266b3975c51dc22
