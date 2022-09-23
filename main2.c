#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

struct player{
    char pname[50];
    int run;
    int wickets;
    int strate;
    int bfaced;
    int obowled;
    int rgiven;
    int economy;
    bool out;
};

struct team
{
    int toss;
    char tname[50];
    int totalRun;
    int totalWickets;
    struct player p[11];
    int fbatting;
}A,B;

int toss();
void getpDetails(struct team *,struct team *,int);
void pname(struct team*, int, int);
void innings(struct team *, struct team *,int,int,int);
int newBatsman(struct team*, int);
int changeBowler(struct team*, int);
void winner(struct team*, struct team*, int);
void summary(struct team*, struct team*,int);

int main()
{   
    int n, overs =0,tossch,fbatting;
    struct team *a, *b;

    a=&A;
    b=&B;
    
    printf("Enter the no.of.overs: ");
    scanf("%d",&overs);

    printf("Enter no.of.players: ");
    
    scanf("%d",&n);

    getpDetails(a,b,n);

    printf("Who is tossing?\n1.%s\t2.%s\nEnter the 1 or 2: ",A.tname,B.tname);
    scanf("%d",&tossch);

    if(tossch==1)
    {
        A.toss=toss();
        printf("%s Choose 1.Head or 2.Tails\n Enter 1 or 2:",B.tname);
        scanf("%d",&B.toss);
        if(A.toss==B.toss)
        {
            printf("Huray!!!%s won the toss\n",B.tname);
            printf("%s Chooses 1.Batting 2.Fielding\nEnter 1 or 2:",B.tname);
            scanf("%d",&B.fbatting);
        }
        else
        {
            printf("Huray!!!%s won the toss\n",A.tname);
            printf("%s Chooses 1.Batting 2.Fielding\nEnter 1 or 2:",A.tname);
            scanf("%d",&A.fbatting);
        }
    }
    else
    {
        B.toss=toss();
        printf("%s Choose 1.Head or 2.Tails\n Enter 1 or 2:",A.tname);
        scanf("%d",&A.toss);
        if(A.toss==B.toss)
        {
            printf("Huray!!!%s won the toss\n",A.tname);
            printf("%s Chooses 1.Batting 2.Fielding\nEnter 1 or 2:",A.tname);
            scanf("%d",&A.fbatting);
        }
        else
        {
            printf("Huray!!!%s won the toss\n",B.tname);
            printf("%s Chooses 1.Batting 2.Fielding\nEnter 1 or 2:",B.tname);
            scanf("%d",&B.fbatting);
        }

    }

    if(A.fbatting==1 || B.fbatting == 2)
    {   
        printf("\t\t%s\t\t\n",A.tname);
        innings(a,b,n,overs,1);
        summary(a,b,n);
        printf("\t\t%s\t\t\n",B.tname);
        innings(b,a,n,overs,2);
        winner(a,b,n);
        summary(b,a,n);
    }
    else
    {   
        printf("\t\t%s\t\t\n",B.tname);
        innings(b,a,n,overs,1);
        summary(b,a,n);
        printf("\t\t%s\t\t\n",A.tname);
        innings(a,b,n,overs,2);
        winner(b,a,n);
        summary(a,b,n);
    }    

    
}

int toss()
{
    int toss;

    srand(time(0));
    toss = (rand() % (1 - 0 + 1)) + 0;

    return toss;

}

void getpDetails(struct team *a, struct team *b, int n)
{
    printf("Enter name of TeamA:");
    scanf(" %[^\n]",a->tname);
    a->totalRun = 0;
    a->totalWickets = 0;


    printf("Enter Details of Players of %s\n**********************************************\n",a->tname);

    for (int i = 0; i < n; i++)
    {
        printf("Enter Name of Player %d: ",i+1);
        scanf(" %[^\n]",a->p[i].pname);

        a->p[i].run = 0;
        a->p[i].out =0;
        a->p[i].strate = 0;
        a->p[i].wickets =0;
        a->p[i].bfaced =0;
        a->p[i].obowled =0;
        a->p[i].rgiven =0;
    }

    printf("Enter name of TeamB:");
    scanf(" %[^\n]",b->tname);   
    b->totalRun = 0;
    b->totalWickets = 0;

    printf("Enter Details of Players of %s\n**********************************************\n",b->tname);

    for (int i = 0; i < n; i++)
    {
        printf("Enter Name of Player %d: ",i+1);
        scanf(" %[^\n]",b->p[i].pname);

        b->p[i].run = 0;
        b->p[i].out =0;
        b->p[i].strate = 0;
        b->p[i].wickets =0;
        b->p[i].bfaced =0;
        b->p[i].obowled =0;
        b->p[i].rgiven =0;
    }
    

    
}

void pname(struct team* T, int n, int ch)
{
    printf("Players of Team\n\n");

    if (ch == 1)
    {
        for (int i = 0; i < n; i++)
        {
            printf("%d. %s\n",i+1,T->p[i].pname);
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (T->p[i].out == 0)
            {
                printf("%d. %s\n",i+1,T->p[i].pname);  
            }
        
        }
    }
    
}

void innings(struct team *bat, struct team *bowl,int n,int o,int ch)
{
    int cOver = 0, bCount, temp,run;
    bool wicket;
    int strike, nonstrike, bowler;
    float currunRate, reqrunRate;
    pname(bat,n,2);

    printf("Enter the number of Player in Strike: ");
    scanf("%d",&strike);
    bat->p[strike-1].out = 1;
    printf("Enter the number of Player in Non-strike: ");
    scanf("%d",&nonstrike);
    bat->p[nonstrike-1].out = 1;


    pname(bowl,n,1);
    printf("Enter the number of the bowler: ");
    scanf("%d",&bowler);
    bowl->p[bowler-1].obowled += 1;

    while ((cOver<=o-1))
    {
        if (bCount == 6)
        {
            temp = strike;
            strike = nonstrike;
            strike = temp;
        }

        bCount = 1;

        if(ch == 2)
        {
            reqrunRate = (float) (bowl->totalRun - bat->totalRun) / (o-cOver) ;
            printf("Required Run Rate: %f\n",reqrunRate);
        }

        while ((bCount<=6))
        {   
            printf("\nRun Scored in ball %d.%d: ",cOver,bCount);
            scanf("%d",&run);

            bat->p[strike-1].run += run;
            bat->totalRun += run;
            bat->p[strike-1].bfaced += 1;
            bowl->p[bowler-1].rgiven += 1;

            printf("Was it a Wicket\n1.True\t0.False: ");
            scanf("%d",&wicket);
            printf("Run:%d\n",run);
            if (wicket)
            {
                bowl->p[bowler-1].wickets += 1;
                bowl->totalWickets += 1;
                if(bowl->totalWickets == n-1)
                {return;}
                strike = newBatsman(bat,n);
                bat->p[strike-1].out = 1;
            }
            if (ch == 2)
            {
                if (bowl->totalRun < bat->totalRun)
                {
                    return ;
                }
                
            }
            
            if (run%2==1)
            {
                temp = strike;
                strike = nonstrike;
                strike = temp;
            }
                
            bCount += 1;

        }

        cOver += 1;

        bowler = changeBowler(bowl,n);
        bowl->p[bowler-1].obowled += 1;

        currunRate = (float) bat->totalRun / cOver;
        printf("Current Run Rate: %f\n",currunRate);
        
        
    }
    
}

int newBatsman(struct team* bat, int n)
{
    int strike;

    pname(bat,n,2);
    
    printf("Enter the number of Player in Strike: ");
    scanf("%d",&strike);

    return strike;

}

int changeBowler(struct team* bowl, int n)
{
    int bowler;

    pname(bowl,n,1);

    printf("Enter the number of the bowler");
    scanf("%d",&bowler);

    return bowler;
}

void winner(struct team* i1, struct team* i2, int n)
{
    if(i1->totalRun > i2->totalRun)
    {
        printf("%s won by %d runs.\n",i1->tname,i1->totalRun - i2->totalRun);
    }
    else if(i1->totalRun == i2->totalRun)
    {
        printf("Draw match");
    }
    else
    {
        printf("%s won by %d wickets\n",i2->tname, n - i2->totalWickets);
    }
}

void summary(struct team* A, struct team* B,int n)
{
    printf("\n\t\t%s\n",A->tname);

    printf("Name\t\tRuns\t\tSrike Rate\n");
    for (int i = 0; i < n; i++)
    {   
        A->p[i].strate = ( (float) A->p[i].run / A->p[i].bfaced ) * 100;
        if (A->p[i].bfaced == 0)
        {
            A->p[i].strate = 0;
        }
        
        printf("%d.%s\t\t%d\t\t%d\n",i+1,A->p[i].pname,A->p[i].run,A->p[i].strate);
    }

    printf("\n");
    printf("Name\t\tOvers\t\tEconomy\n");
    for (int i = 0; i < n; i++)
    {
        B->p[i].economy = ((float) B->p[i].rgiven / B->p[i].obowled);
        if (B->p[i].obowled == 0)
        {
            B->p[i].economy = 0;
        }

        printf("%d.%s\t\t%d\t\t%d\n",i+1,B->p[i].pname,B->p[i].obowled,B->p[i].economy);
        
    }
    
}