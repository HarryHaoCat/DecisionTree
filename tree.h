/*************************************************************************
	> File Name: tree.h
	> Author: HarryHao
	> Mail: 95487858@qq.com 
	> Created Time: 2018年07月11日 星期三 10时48分10秒
 ************************************************************************/

#ifndef _TREE_H_
#define _TREE_H_
#define NOTHING 111
//天气值域
#define SUNNY     11
#define VOERCAST     12
#define RAIN 13
//风值域
#define WIND  2
#define NO_WIND     3
//类别属性值域
#define CAN_PLAY      14
#define NOT_PLAY      15
//非类别属性值域
#define OUTLOOK       16
#define TEMPERATURE      17
#define HUMIDITY      18
#define WINDY     19
//将温度分三个类
#define HIGH_TEMPERATURE  8
#define MID_TEMPERATURE    7
#define COLD_TEMPERATURE  6
//将湿度分两个类
#define HIGH_HUMIDITY          75
#define NORMAL_HUMIDITY    74
#define TRAINING_NUMBER    14
//训练数据集结构
typedef struct TRAINING
{

int outLook;
int temperature;
int humidity;
int windy;
int play;
struct TRAINING *next;  //定义下一结点的指针
}TRAINING;

//决策树结构
typedef struct TREE
{
int attribute;
struct TREE *left;
struct TREE *mid;
struct TREE *right;
}TREENODE,*TREE;

//建立训练数据的链表
TRAINING* trainingInit(TRAINING trainingSet[]); 
//按照属性值划分数据集
TRAINING* splitData(int feature, int class, TRAINING* head);
//计算某个划分子集的信息熵
double calEntropy(TRAINING* head);
//计算log2函数
double log2(double x);
//计算信息熵
double Entropy(double p1, double p2);
//计算某个子集的个数
double num(TRAINING* head);
//子集划分结束的标志：如果属于同一类则划分结束，返回类标签
int IsOneClass(TRAINING* head);
//用完所有的属性依然不属于同一类，则最多的类为类标签
int majorityCnt(TRAINING* head);
//计算某个属性的信息熵,选取最好的划分属性
int choseBestFeature(TRAINING* p);
//建树函数载入，传入数据集的头指针和指向子节点的指针,递归创建树
void createTree(TREE* tree, TRAINING* head);
//分类函数
int classify(TREE* tree, TRAINING* head);
//打印决策树
void printTree(TREE* tree, int location);
#endif





