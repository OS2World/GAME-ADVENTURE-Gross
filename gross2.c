/*

NOTE -- when compiling for os/2 on the gcc compiler do this:
        gcc -c gross.c   **creates the obj file
        gcc -o gross2.exe gross2.obj -static  **links without the need for dllc.dll

    this creates a bigger executable, but it is standalone - doesn't need
    the dllc.dll file (which is in gnu\dl

**
**
**

**

**


*/

#include <stdio.h>

#define NUTHIN -1
#define NUMVERB 35   /* # of verbs    */
#define NUMNOUN 41      /* # of objects                 */
#define NUMCARRY 4      /* max # of objects carried     */
#define NUMROOM 12      /* number of rooms in the house */
#define LIGHTSPAN 120   /* # of turns the candle lasts  */

char *getit();

main()
    {
    int i = 0, j = 0, k = 0, z = 0;
    int verbnum = 0;
    int  nounum = NUTHIN;
    int  holder;
    int roomnum = 4;    /* start in entry hall(5) during development */
    int space = 32;     /* the porch is 4 */
    int dirchar;
    int doorflag = 0;   /* 1 if front door is unlocked from outside */
    /* int verbose = 0;    0 if verbose descriptions on */
    int outflag = 0;    /* 1 if front door is unlocked from inside */
    int lightlife = 0;  /* candle lit; '++' each turn; max is LIGHTSPAN*/
    int light = 0;      /* 1 if light is lit */
    int cakekey = 0;    /* 1 if you have eaten the cake with the key */
    int wearem = 0;     /* 1 if you are wearing the old clothes */
    int wearwig = 0;    /* 1 "   "   "    "      "  wig */
    int mirclean = 0;   /* 1 if you have cleaned the mirror  */
    int trunkop = 0;    /* 1 if the trunk is unlocked */
    int stink = 0;      /* 1 if you have been 'flush'ed and smell bad */
    int roomtime = 0;   /* # of times in the same room with wizard */
    int health = 100;   /* 100 health points to start */
    int turn = 0;       /* # of turns taken so far */
    int scratches = 0;  /* 0 if not scratched, 1 if scratched */
    int wearscarf = 0;  /* 1 if wearing scarf */
    int wearboots = 0;  /* 1 if wearing the small white boots */
    int bats = 0;       /* 1 if bats driven from b. bedroom */
    int puke = 0;       /* 1 if you have puked */
    int wearneck = 0;   /* 1 if wearing the bracelet */

    int carry[NUMCARRY];
    int obloc[NUMROOM][NUMNOUN];

    char answer[2];
    char buff[130];
    char firwrd[25], secwrd[25];
    char *verbs[NUMVERB] = {
                "get",      /* 0 */
                "drop",
                "go",       /* 2 */
                "have?",
                "knock on", /* 4 */
                "unlock",
                "read",     /* 6 */
                "light",
                "north",    /* 8 */
                "south",
                "east",     /* 10 */
                "west",
                "n",        /* 12 */
                "s",
                "e",        /* 14 */
                "w",
                "examine",  /* 16 */
                "?",
                "open",     /* 18 */
                "wear",
                "clean",    /* 20 */
                "eat",
                "drink",    /* 22 */
                "help",
                "look",     /* 24 */
                "quit",
                "vacuum",   /* 26 */
                "cut",
                "say",      /* 28 */
                "puke",
                "flush",    /* 30 */
                "snuff",
                "remove",   /* 32 */
                "turn",
                "health",   /* 34 */
                };
                        /*  35 TOTAL
                        when you add a verb
                        change the value of
                        NUMVERB */

            /*
               don't add any verbs to the list that have as
               their first letter e n s or w
               unless it is after these letters sequentially
               in the list
            */

    char *nouns[NUMNOUN] = {
                "the matches",          /* 0 */
                "the candle",
                "the small brass key",  /* 2 */
                "the rusty iron key",
                "the door",             /* 4 */
                "the silver key",
                "the doormat",          /* 6 */
                "the bats",
                "north",                /* 8 */
                "south",
                "east",                 /* 10 */
                "west",
                "the cake",             /* 12 */
                "the ghostly wizard",
                "the scarf",            /* 14 */
                "the goblet",
                "the mirror",           /* 16 */
                "some dust",
                "the trunk",            /* 18 */
                "the vacuum",
                "the book",             /* 20 */
                "the old clothes",
                "the wig",              /* 22 */
                "the knife",
                "the puke",             /* 24 */
                "a small piece of cake",
                "igot tago",            /* 26 */
                "something faintly shining",
                "the toilet",           /* 28 */
                "yourself",
                "the broken mirror",     /* 30 */
                "the small white boots",
                "the bracelet",          /* 32 */
                "the newspapers",
                "the decomposing bat",     /* 34 */
                "the stove",
                "the garbage",           /* 36 */
                "the Pong game",
                "the porch",             /* 38 */
                "the rats",
                "the white liquid"       /* 40  */
                };
                        /* -- 41 TOTAL
                        when you add a noun
                        change the value of
                        NUMNOUN  */

    char *rooms[NUMROOM] = {
               "in the kitchen",
               "in the dining room",
               "in the north bedroom",
               "in the bathroom",
               "on the porch in front of the door of the house",
               "in the entry hall",
               "in the upstairs hall",
               "in the back bedroom",
               "in the library",
               "in the living room",
               "in the south bedroom",
               "in the basement"
               };

    char *directions[NUMROOM] = {"ew",  "sw",   "s",    "?",
                     "x",   "nse",  "nsew", "w",
                     "e",   "nw",   "n",    "e"};

    char *description[NUMROOM] =
                {
"filthy. Something horrible is simmering and gurgling on the stove.",
"dominated by a table covered with dirty dishes.",
"littered with books and manuscripts.",
"very warm and smells absolutely awful.",
"littered with old newspapers, garbage, and a decomposing bat.",
"dark. You can barely see.",
"dim, but you can see three doorways.",
"messy.",
"filled with stacks of books. You see some small puddles of candle wax.",
"covered in dust at least an inch thick.",
"dim.  You can see black things on the floor.  Some are moving.",
"full of cobwebs that get in your mouth and nose."
                };
    char *direc[NUMROOM] =
                {
"There is a door to the west and to the east.",
"There is a door to the west and to the south.",
"There is a door to the south.",
"There are no doors in this room.",
"There is one door to the east.",
"To the north and south are open doors, a door west, and a stairway east.",
"There are doors to the north, south, and east, and a stairway west.",
"There is a door to the west.",
"There is a door to the east.",
"There is a door to the north and to the west.",
"There is a door to the north.",
"To the east there are stairs that lead up to a door."
                };

    for(i = 0; i < NUMCARRY; i++)
        {
        carry[i] = NUTHIN;
        }

    for(i = 0; i < NUMROOM; i++)
        {
        for(j = 0; j < NUMNOUN; j++)
            {
            obloc[i][j] = NUTHIN;
            }
        }
/* kitchen */   obloc[0][0] = 0;    /*  matches */
                obloc[0][1] = 23;   /*  knife   */
                obloc[0][2] = 35;   /*  stove */

/* d. room */   obloc[1][0] = 1;    /*  candle  */
                obloc[1][1] = 12;   /*  cake    */
                obloc[1][2] = 15;   /*  goblet  */

/* n. bedrm */  obloc[2][0] = 31;   /*  boots     */
                obloc[2][1] = 13;   /*  ghostly wizard  */

/* bathroom */  obloc[3][0] = 28;   /*  toilet */

/* porch  */    obloc[4][0] = 6;    /*  doormat */
                obloc[4][1] = 33;   /*  newspapers */
                obloc[4][2] = 36;   /*  garbage */
                obloc[4][3] = 34;   /*  decomposing bat */

/* entryhall */

/* b. bedrm */  obloc[7][0] = 7;    /*  bats    */
                obloc[7][1] = 14;   /*  scarf     */

/* library  */  obloc[8][0] = 20;   /*  book  */

/* l.room   */  obloc[9][0] = 19;   /*  vacuum */
                obloc[9][1] = 37;   /*  Pong game */
                obloc[9][2] = 17;   /* the dust */

/* s. bedrm */ obloc[10][0] = 22;   /*  wig */
               obloc[10][1] = 32;   /*  bracelet */
               obloc[10][2] = 39;   /*  rats */

/* bsmnt    */  obloc[11][0] = 18;  /*  trunk  */
                obloc[11][1] = 16;  /*  mirror */


                    /*
                       clothes[21] in trunk
                       brass key[2] in cake
                       silver key[5] behind the mirror
                       iron key[3] under the doormat
                    */


/*
the long if() below decides if you are in a room that is too dark to see
if you are then the candle must be lit and carried or in the room before
you can see what is in the room.

currently only partially done -- does not check to see that the candle
is carried
**
*/
    setup();
    restart:
    turn++;
    if(turn == 200 && scratches == 1)
        {
        printf("The wounds from the lizard bites and scratches have become infected.\n");
        health = health - 23;
        }
    if(health <= 0)
        {
        death(turn); /* needs parameters for kind of damage done */
        }
    printf("\nYou are standing %s.\n", rooms[roomnum]);
if((light == 0 && (roomnum != 3 && roomnum != 10 && roomnum != 8)) || light == 1)
    {
    printf("It is %s\n", description[roomnum]);
    printf("%s\n",direc[roomnum]);
        if(roomnum == 2 && seeit(13,roomnum,obloc) != NUTHIN)
            {                                   /* if the wizard is there */
            descriptions(roomnum);              /* then print the         */
            }                                   /* description of the n.  */
                                                /* bedroom                */
        printf("\n");
    if(roomnum == 2 && roomtime < 3)
        {
        roomtime++;
        if(roomtime == 3 && seeit(13,roomnum,obloc) != NUTHIN)
            {
            roomtime = 0;
            health = health - 10;                                   /* too long in the room   */
            roomnum = byebye();
            goto restart;                           /* with the wizard and he */
            }                                       /* teleports you out      */
        }
    if(roomnum == 3 && seeit(13, roomnum, obloc) != NUTHIN)
        {
        health = health - 10;                         /* if you are in the bathroom with */
        roomnum = brbye();
        goto restart;                 /* the wizard then you are gone    */
        }
    if(roomnum == 4 && scratches == 1)
        {
        wonit(health,turn);
        exit(0);               /* you have to win the game */
        }                      /* if on the porch and have been damaged */

    printf("You can see: ");
    for(i = 0,k = 0, z = 0; i < NUMNOUN; i++)  /* used to be NUMCARRY */
        {
        if(obloc[roomnum][i] != NUTHIN)
            {
            z++;
            k++;              /* this wraps the line  */
            if(k == 4)        /* around after 4 nouns */
                {
                printf("\nand ");
                k = 0;
                }
            printf("%s, ",nouns[obloc[roomnum][i]]);
            }
        }
    if(z == 0)  /* if z==0, then no nouns printed, so BS over "You can see" */
        {
        for(i = 0; i < 13; i++)
            {
            putchar(8);
            }
        }
    else{
    putchar(8);     /* this backspaces over the space and the colon or comma  */
    putchar(8);     /* at the end of the 'You can see ' string  */
    putchar(46);    /* and then puts a period and a linefeed in */
    putchar(10);
    putchar(13);
        }
    }
    if(light == 1)
        {
        lightlife++;
        if(lightlife == LIGHTSPAN)
            {
            light = 0;
            printf("\nYour candle burns to a nubbin.  You don't notice this\n");
            printf("until it burns as far as your fingers and scorches them.\n");
            printf("The candle goes out as you shake your hand in pain.\n");
            health = health - 2;
            }
        }

    printf("What will you do now?\n");
/*    fflush(stdout);  */
    fflush(stdin);

    getit(buff);  /* rewritten gets() function from lib of gcc to eliminate warning in original lib src code for gets() */
    if(buff[0] == '\0')
        {
        goto restart;
        }
    if(strchr(buff,space) == NULL)
        {
        for(i = 0,j = 0; buff[i] != '\0'; ++i,++j)
            {
            firwrd[j] = buff[i];
            }
        firwrd[i] = '\0';
        }
    else
        {
        for(i = 0,j = 0; buff[i] != space; ++i,++j)
            {
            firwrd[j] = buff[i];
            }
        firwrd[i] = '\0';
        }
    j = 0;
    holder = i;
    while (strncmp(firwrd, verbs[j], i) != 0)
        {
        j++;
        if(j == NUMVERB) /* if it counts up to the # of verbs then it can't find that verb in the list so you can't do it */
            {
            printf("You %s for a bit.  Nothing interesting or useful happens.\n", firwrd);
            goto restart;
            }
        }

    verbnum = j;
    switch(verbnum)
                /* abbreviations for verbs and
                   -some- one verb
                   commands are intercepted here.
                   the one verb commands could
                   be put in the switch following
                   verbcases
                   And some verbs 'get' and 'drop' are
                   intercepted here -- error messages for
                   them are in verbcases
                */
        {
/*      case(0):
            goto verbcases;
        case(1):
            goto verbcases;       */

        case(8):    /*  north */
            verbnum = 2;
            nounum =  8;
            goto verbcases;
        case(9):    /* south */
            verbnum = 2;
            nounum = 9;
            goto verbcases;
        case(10):   /* east */
            verbnum = 2;
            nounum = 10;
            goto verbcases;
        case(11):   /* west */
            verbnum = 2;
            nounum = 11;
            goto verbcases;
        case(12):   /* n */
            verbnum = 2;
            nounum =  8;
            goto verbcases;
        case(13):   /* s */
            verbnum = 2;
            nounum = 9;
            goto verbcases;
        case(14):   /* e */
            verbnum = 2;
            nounum = 10;
            goto verbcases;
        case(15):   /* w */
            verbnum = 2;
            nounum = 11;
            goto verbcases;
        case(24):   /* look */
            if((roomnum == 8 || roomnum == 10) && light == 0)
                {
                printf("It is to dark to see much.\n");
                goto restart;
                }
            else
                {
                printf("\n");
                descriptions(roomnum);
                goto restart;
                }
        case(33):  /* turn */
            printf("This is turn %d.\n",turn);
            goto restart;
        case(34):  /* health */
            healthy(health);
            goto restart;
        }

/*
the 'if' below checks to see if there is a return immediately after
the verb.  if there is, then nounum is set to -1 (NUTHIN - no known noun)
and the program goes off to verbcases as these verbs don't need nouns.
*/
    if(buff[i] == '\0')
        {
        nounum = NUTHIN;
        goto verbcases;
        }

    j = 0;
    i++;
    while (buff[i] != '\0')
        {
        secwrd[j] = buff[i];
        j++;
        i++;
        }
    secwrd[j] = '\0';
    j = 0;
    k = i - holder--;

    while (strncmp(secwrd, nouns[j], k) != 0)
        {
        j++;
        if(j == NUMNOUN)
            {
            if(verbnum == 28)  /* intercept 'say' words that are not useful */
                {
                printf("You say '%s'.  Nothing interesting or useful happens.\n", secwrd);
                goto restart;
                }
                else
                {
                printf("You can't %s %s right now.\n",firwrd,secwrd);
                printf("Perhaps you will be able to do this another time.\n");
                goto restart;
                }
            }
        }
    nounum = j;
    verbcases:
    printf("\n");
switch(verbnum)
        {

/* get */   case(0):

    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

        if(light == 0 && (roomnum == 3 || roomnum == 8 || roomnum == 10))
            {
            printf("It is too dark to see  %s here.  Nevertheless\n", nouns[nounum]);
            printf("you fumble about but you can't seem to find %s.\n", nouns[nounum]);
            goto restart;
            }

        if((k = seeit(nounum, roomnum, obloc)) != NUTHIN)
                {
            if(nounum == 18 || nounum == 16 || nounum == 4 || nounum == 17 || nounum == 28 || nounum == 30 || nounum == 35 || nounum == 24 || nounum == 36 || nounum == 39)
                {                                                                                          /* the above list of nouns are things */
                printf("You can't get %s in this game.  If you look around your own\n", nouns[nounum]);    /* that can't be got.  statemnt could */
                printf("house you may find that you already have %s.  You will have\n", nouns[nounum]);    /* be simpler if all of them were above */
                printf("to be satisfied with that.\n");                                                    /* a certain number  */
                goto restart;
                }
            if(nounum == 31 && roomnum == 2)
                {
                if(seeit(13,roomnum,obloc) != NUTHIN)
                    {
                    printf("You reach for the small white boots, but something happens as you do.\a\n");
                    health = health - 10;
                    roomnum = byebye();
                    goto restart;
                    }
                }
            if(roomnum == 3 && nounum == 27)
                {
                for(i = 0; i < NUMCARRY; i++)
                    {
                    if(carry[i] == NUTHIN)
                        {
                        carry[i] = 2;
                        printf("The something faintly shining is a small brass key.\n");
                        for(k = 0; k < NUMNOUN; k++)
                            {
                            if(obloc[roomnum][k] == 27)
                                {
                                obloc[roomnum][k] = NUTHIN;
                                goto restart;
                                }
                            }
                        }
                    }
                if(i == 4)
                    {
                    printf("You can't carry anything else.\n");
                    goto restart;
                    }
            }


    for(i = 0; i < NUMCARRY; i++)
        {
        if(carry[i] == NUTHIN)
            {
            carry[i] = nounum;
            obloc[roomnum][k] = NUTHIN;
            printf("You now have %s.\n",nouns[nounum]);
            if(roomnum == 4 && nounum == 6)  /* iron key appears */
                {
                obloc[4][1] = 3;
                printf("You notice a rusty iron key under the mat!\n");
                }
            if(nounum == 19)
                {
                printf("As you pick up the vacuum, some of the yellow-white ooze\n");
                printf("burns a hole through skin on the palm of your hand.\n");
                health = health - 4;
                }
            goto restart;
            }
        }
        printf("You can't get %s because you can't carry any more.\n",nouns[nounum]);
        goto restart;
    }
    printf("Sorry, %s isn't here. You can't get it.\n", nouns[nounum]);
    break;


/* drop */  case(1):

    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }
/*
-- the first if() checks to see if you have it to drop and then removes
   the thing from the list
   of things carried in carry[]
-- the second if() puts the
   thing dropped into the list
   of things in the room obloc[][] at the first empty spot
*/
    if((k = carryit(nounum, carry)) != NUTHIN)
        {
        printf("You have just dropped %s\n",nouns[nounum]);
        carry[k] = NUTHIN;
        if(nounum == 1)  /* if you drop the candle it goes out */
            {
            if(light == 1) /* if it is lit */
                {
                printf("The candle flickers and goes out.\n");
                light = 0;
                }
            }

    if(roomnum == 2 && nounum == 20 && (seeit(13, roomnum, obloc) != NUTHIN)) /* in b.room, drop the book, wizard is there */
        {                          /* if n.bedrm, if book, if wizard there */
        for(i = 0; i < NUMNOUN; i++)
            {
            if(obloc[roomnum][i] == 13)
                {
                obloc[roomnum][i] = 20;   /* book replaces wizard */
                for(j = 0; j < NUMNOUN; j++)
                    {
                    if(obloc[3][j] == NUTHIN)
                        {
                        obloc[3][j] = 13; /* wizard to bathroom */
                        break;
                        }
                    }
                break;
                }
            }

        printf("The ghostly wizard sees the book and quickly picks it up.\n");
        printf("He leafs through it hurriedly, pauses with a hideous look of\n");
        printf("delight and relief on his face, and says a couple of words.\n");
        printf("You can't hear what he says, but it is not important.  Dropping\n");
        printf("the book, he fades away as you watch.\n");
        goto restart;
        }

        for(k = 0; k < NUMNOUN; k++)
            {
            if(obloc[roomnum][k] == NUTHIN)
                {
                obloc[roomnum][k] = nounum;
                goto restart;
                }
            }
        }

    printf("Sorry, you don't have the %s to drop.\n", nouns[nounum]);
    break;

/* go */    case(2):
        switch(nounum)
            {
            case(8):
                dirchar = 110;  /* n */
                break;
            case(9):
                dirchar = 115;  /* s */
                break;
            case(10):
                dirchar = 101;  /* e  */
                break;
            case(11):
                dirchar = 119;  /*  w  */
                break;
            }


        if(roomnum == 4 && doorflag == 0 && nounum == 10)
            {
            printf("\nYou try to open the door, but it is locked.\n");
            goto restart;
            /* can't go in the house until door is unlocked */
            }

        if(roomnum == 4 && doorflag == 1 && nounum == 10)
            {
            printf("\nYou walk east directly into the door.\n");
            printf("Then you take a step back and gently rub your injured nose.\n");
            health--;
            goto restart;
            /* door is unlocked but not open */
            }
        if(roomnum == 4 && doorflag == 2 && nounum == 10)
            {
            printf("\nYou enter the house.\n");
            printf("The door slams shut behind you!\n");
            }
        if(roomnum == 4 && nounum != 10)
            {
            verbnum = 25;
            goto verbcases;
            }
                /*
                if you want to leave the porch then
                you are quitting the game, in effect
                */
        if(roomnum == 5 && outflag == 1 && nounum == 11)
            {
            printf("\nYou walk west directly into the door.\n");
            printf("Then you take a step back and gently rub your injured nose.\n");
            health--;
            goto restart;
            /* door is unlocked but not open */
            }

        if(roomnum == 5 && outflag == 2 && nounum == 11)
            {
            printf("\nYou leave the house.\n");
            printf("The door slams shut behind you!\n");
            /* endgame() function here */
            }
        if(roomnum == 5 && nounum == 10)
            {
            printf("\nYou climb the steep stairs to the east.\n");
            }
        if(roomnum == 0 && nounum == 11)
            {
            printf("\nYou walk down the narrow, dark stairs.\n");
            }
        if(strrchr(directions[roomnum],dirchar) == NULL)
            {
            printf("\nSorry, you can't go that way.\n");
            goto restart;
            }

        switch(nounum)
            {
            case(8):
                roomnum = roomnum - 4;
                break;
            case(9):
                roomnum = roomnum + 4;
                break;
            case(10):
                roomnum = roomnum + 1;
                break;
            case(11):
                roomnum = roomnum - 1;
                break;
            default:
                printf("Can't go that way.\n");
                goto restart;
            }
        if(roomnum < 0) roomnum = roomnum + 12;     /* keeps roomnumbers over */
        if(roomnum == 12) roomnum = roomnum - 12;   /* 0 and < 12             */
        if(roomnum == 7 && stink == 0)
            {
    printf("You go into the back bedroom.  There are bats there.\n");
    printf("The bats smell you come into the room.  They attack, and\n");
    printf("they seem to like your face.  You try to defend yourself\n");
    printf("but they are too fierce.  Bleeding from many small bites\n");
    printf("on your nose, ears and lips, you back out of the room and into\n");
    printf("the hall.  Fortunately the bats do not follow you.\n");
            health = health - 11;
            roomnum = 6;
            goto restart;
            }
        if(roomnum == 7 && stink == 1)  /* if you stink and are in b. bedroom */
        {
            if(bats == 0)               /* if you haven't driven off the bats already  */
            {
    printf("You go in the back bedroom.  There are bats there.\n");
    printf("The bats smell you come into the room.  They smell the brown\n");
    printf("lumpy liquid that covered you when you were flushed.  The\n");
    printf("bats quickly leave the room through a crack in the ceiling.\n");
            for(i = 0; i < NUMNOUN; i++)
                {
                if(obloc[roomnum][i] == 7)
                    {
                    obloc[roomnum][i] = NUTHIN;
                    break;
                    }
                }
                bats = 1;
            }
        }
        if(roomnum == 10 && wearboots == 0)
            {
            printf("You walk into the south bedroom.  The rats hear you enter.\n");
            printf("They are happy because you are the first bit of live food\n");
            printf("they have come across in some time.  They go directly for your\n");
            printf("ankles and take a few pretty good chunks from them before you\n");
            printf("get out of the room.  Blood runs into your shoes.\n");
            printf("The rats return to the darkness.\n");
            health = health - 9;
            roomnum = 6;
            }
        if(roomnum == 10 && wearboots == 1)
            {
            printf("The rats hear you enter the room.  They are happy because you are\n");
            printf("the first bit of live food they have come across in some time.  They go\n");
            printf("directly for your ankles and take a few pretty good chunks from your boots.\n");
            printf("They don't like the taste and return to the dark corners of the room.\n");
            }
        break;

/* have? */ case(3):
        printf("You have on your regular clothes.\n");
        if(scratches == 1)
            {
            printf("Except, of course, for your pants, which you left with the lizard.\n");
            }
        if(wearem == 1)
            {
            printf("You are also wearing the old clothes.\n");
            }
        if(wearwig == 1)
            {
            printf("You are wearing the wig too.\n");
            }
        if(wearscarf == 1)
            {
            printf("You are wearing the scarf around your neck.\n");
            }
        if(wearboots == 1)
            {
            printf("You have on the small white boots.  They are so cute.\n");
            }
        if(wearneck == 1)
            {
            printf("You have a bracelet of small white skulls around your wrist.\n");
            }
        if(scratches == 1)
            {
            printf("You no longer have part of your left thumb.\n");
            }
        printf("You have ");
        for(i = 0,k = 0, z = 0;i < NUMCARRY; i++)
            {
            if(carry[i] >= 0)
                {
                z++;
                k++;
                if(k == 4)
                    {
                    printf("and\n");
                    k = 0;
                    }
                printf("%s, ",nouns[carry[i]]);
                }
            }
        if(z == 0)
            {
            for(i = 0;i < 9;i++){putchar(8);}
            printf("You don't have anything else right now.\n");
            }
        else{
        putchar(8);
        putchar(8);
        printf(".\n");
            }
        break;

/* knock */ case(4):
        if(nounum == 4)
            {
            knock(nounum,roomnum);
            goto restart;
            }

        if(seeit(nounum, roomnum, obloc) != NUTHIN)
            {
            knock(nounum,roomnum);
            goto restart;
            }

        if(carryit(nounum, carry) != NUTHIN)
            {
            knock(nounum, roomnum);
            goto restart;
            }

printf("You hear the sound of your knuckles hitting the %s\n",nouns[nounum]);
printf("Nothing happens.\n", nouns[nounum]);
            break;

/* unlock */
        case(5):

    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

        switch(roomnum)
            {
            case(4):         /* on the front porch */
                if(nounum == 4)  /* if you are unlocking the door */
        {
        if(carryit(3,carry) != NUTHIN)  /* if you have the rusty iron key */
            {
                            doorflag = 1;
                            directions[roomnum] = "e";
                            printf("The key squeaks in the door's rusty lock as it turns. The door is unlocked.\n");
                            printf("Bats fly out from under the porch eaves.  You hear them squeaking too.\n");
                            goto restart;
                            }
            else
            {
            printf("You don't yet have the key that unlocks the front door.\n");
            goto restart;
            }
               }
          else
            {
             printf("You can't unlock %s in this game.\n",nouns[nounum]);
             printf("I wouldn't try it at home either!\n");
             goto restart;
             }


            case(5):    /* in the entry hall */
                if(nounum == 4)  /* if you are unlocking the door */
        {
        if(carryit(5,carry) != NUTHIN)  /* if you have the silver key */
            {
                            outflag = 1;
                         directions[roomnum] = "nsew";
                         printf("The key turns easily in the lock. The door is unlocked. You hear a deep\n");
                         printf("groan from somewhere behind you in the house.\n");
                         goto restart;
                         }
                        else
            {
                    printf("You don't seem to have the key that unlocks this door.\n");
                         goto restart;
            }
              }
         else
        {
        printf("You can't unlock %s in this game.\n",nouns[nounum]);
        printf("I wouldn't try it at home either.\n");
        goto restart;
        }

            case(11): /* in the basement */
            if(nounum == 18) /* the trunk */
                {
                if(carryit(2, carry) != NUTHIN) /* small brass key */
                    {
                    printf("You unlock the trunk with the small brass key.\n");
                    trunkop = 1;
                    goto restart;
                    }
                else
                    {
                    printf("You don't have the key to unlock it.\n");
                    goto restart;
                    }
                }


    case(3):   /* in the bathroom) */
            if(nounum == 4)
                {
                printf("There is no door in the bathroom.\n");
                goto restart;
                }

    default:
         if(nounum == 4)
        {
        printf("The door to this room is not locked.  It's probably open, in fact.\n");
        goto restart;
        }
        else
        {
                printf("You can't unlock %s in this game.\n",nouns[nounum]);
                printf("I wouldn't try it at home either.\n");
        }
    }
        break;

/* read */  case(6):

    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }
            switch(nounum)
                {
                case(20):
                if(seeit(nounum, roomnum, obloc) != NUTHIN)
                    {
                    readit(nounum);
                    break;
                    }
                if(carryit(nounum, carry) != NUTHIN)
                    {
                    readit(nounum);
                    break;
                    }
                case(33):
                if(seeit(nounum, roomnum, obloc) != NUTHIN)
                    {
                    readit(nounum);
                    break;
                    }
                if(carryit(nounum, carry) != NUTHIN)
                    {
                    readit(nounum);
                    break;
                    }
                default:
                printf("You can't read %s in this game.\n", nouns[nounum]);
                }
            break;

/* light */ case(7):

    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }
            switch(nounum)
            {
            case(0):
            if(carryit(nounum, carry) != NUTHIN)
                {
                printf("You light one of the matches.  It flares briefly and\n");
                printf("then goes out, burning your fingers in the process.\n");
                health = health - 1;
                goto restart;
                }
                else
                    {
                    printf("You can't light the matches because you don't have them\n");
                    goto restart;
                    }
            case(1):

        if(light == 1)
            {
            printf("The candle is already lit.\n");
            goto restart;
            }

        if(light == 0 && (roomnum == 3 || roomnum == 8 || roomnum == 10))
            {
            printf("It's so dark you can't see the candle.  You feel around a bit\n");
            printf("frantically, but if it is here you can't find it.  If you have\n");
            printf("lost your only candle in this dark room you are in pretty\n");
            printf("BIG TROUBLE.  You hear faint laughter somewhere in the house.\n");
            goto restart;
            }

        if(carryit(0,carry) != NUTHIN)  /* if you have the matches */
            {
            if(seeit(nounum,roomnum,obloc) != NUTHIN) /* if candle in room */
                {
                printf("You prop the candle upright and light it.  You let go of it and\n");
                printf("it falls over, sputters and goes out.\n");
                goto restart;
                }
            if(carryit(nounum, carry) != NUTHIN)  /* if you have the candle */
                {
                if(lightlife == LIGHTSPAN)
                    {
                    printf("The candle is burnt to a nubbin.  There is nothing left to light.\n");
                    goto restart;
                    }
                printf("You light the candle, burning your fingers as you do.\n");
                health = health - 1;
                light = 1;
                goto restart;
                }
                else
                    {
                    printf("You can't light the candle because it isn't here.\n");
                    goto restart;
                    }
            }
            else
                {
                printf("You don't have anything to light the %s with.\n",nouns[nounum]);
                goto restart;
                }
    default:
    printf("You can't light %s in this game. Don't try this at home either!\n",nouns[nounum]);
    break;
    }
    break;


/* examine */ case(16):

    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

        if(roomnum == 8 && light == 0)
            {
            printf("It is too dim to really see much.\n");
            goto restart;
            }
        if(roomnum == 10 && light == 0)
            {
            printf("It is too dim to really see much.\n");

            goto restart;
            }
        if(roomnum == 3 && light == 0)
            {
            printf("It is too dim to really see much.\n");
            goto restart;
            }
        if(roomnum == 3 && light == 1 && nounum == 24)
            {
            for(i = 0; i < NUMNOUN; i++)
                {
                if(obloc[3][i] == NUTHIN)
                    {
                    obloc[3][i] = 27;  /* something faintly shining appears */
                    break;
                    }
                }
            examine(nounum,roomnum);
            goto restart;
            }

if(roomnum == 11 && nounum == 29 && wearem == 1 && wearwig == 1 && wearscarf == 1 && wearboots == 1 && wearneck == 1)
            if(mirclean == 1)
                {
                printf("You step in front of the clean spot on the mirror\n");
                printf("and look at yourself.  Before the mirror shatters\n");
                printf("in self defense, you have a brief glimpse of a\n");
                printf("hideous creature dressed in mouldy old clothes,\n");
                printf("a slug-ridden wig, a bracelet of small white skulls,\n");
                printf("a garish scarf, and small white boots with hearts\n");
                printf("around the top and tassels on the front.  The creature\n");
                printf("does not seem to be wearing pants and is covered in\n");
                printf("scratches, bites, dried blood and brown lumpy stuff.\n");
                printf("It is missing at least one finger.\n");
                obloc[11][1] = 30;  /* mirror becomes broken mirror */
                goto restart;
                }
            else
                {
                printf("The mirror is so dirty you can't see yourself in it.\n");
                goto restart;
                }

        if(roomnum == 11 && nounum == 30 && obloc[11][1] == 30)
            {
            printf("You examine the broken mirror.  Taped to the back of the\n");
            printf("frame is a silver key.\n");
            for(i = 0; i < NUMNOUN; i++)
                {
                if(obloc[roomnum][i] == NUTHIN)
                    {
                    obloc[roomnum][i] = 5;  /* silver key appears */
                    break;
                    }
                }
            goto restart;
            }

        if(nounum == 4)                   /* if door then                */
            {                             /* examine it even tho you     */
            examine(nounum,roomnum);      /* can't see or carry it       */
            goto restart;
            }

        if(nounum == 38 && roomnum == 4)  /* if on the porch then you */
            {                             /* you can examine porch        */
            examine(nounum, roomnum);
            goto restart;
            }

        if((nounum == 1)  && (carryit(1,carry) != NUTHIN || seeit(1,roomnum,obloc) != NUTHIN))
            {
            printf("You see a small mostly used-up candle with a short wick.\n");
            printf("It does not look like it would last very long.\n");
            if(light == 1)
                {
                printf("The candle is currently lit.\n");
                goto restart;
                }
                else
                    {
                    printf("The candle is currently not lit.\n");
                    goto restart;
                    }
            }

        if(seeit(nounum, roomnum, obloc) != NUTHIN)
            {
            if((mirclean == 1) && (nounum == 16))
                {
                printf("This is an old mirror with a pale white frame, probably made of\n");
                printf("bone.  You have cleaned a large oval area on the surface of the\n");
                printf("glass.  From where you stand you can see the reflection of a dark\n");
                printf("corner of the basement.\n");
                goto restart;
                }
            examine(nounum,roomnum);
            goto restart;
            }

        if(carryit(nounum, carry) != NUTHIN)
            {
            examine(nounum, roomnum);
            goto restart;
            }

if(wearem == 1 || wearwig == 1 || wearscarf == 1 || wearboots == 1 || wearneck == 1)
            {
            examine(nounum,roomnum);  /* if you are wearing something you can */
            goto restart;            /* examine it */
            }

printf("You can't examine %s right now.\n",nouns[nounum]);
printf("Some people find it rewarding to just imagine %s.\n",nouns[nounum]);
        printf("Feel free to do so now.\n");
        break;

/* wearing   case(17):

        break;  */
/* open */  case(18):

    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }
            switch(nounum)
                {
            case(4):
            if(roomnum == 4 && doorflag == 0)
                {
    printf("\nYou try to open the door but it seems to be locked.\n");
                goto restart;
                }
            if(roomnum == 4 && doorflag == 1)
                {
    printf("\nYou open the door.  The sun throws your shadow onto an entry hall.\n");
    printf("A faint whispery voice seems to be calling your name.\n");
                doorflag = 2;
                goto restart;
                }
            if(roomnum == 5 && outflag == 0)
                {
    printf("\nYou try to open the door but it seems to be locked.\n");
                goto restart;
                }
            if(roomnum == 5 && outflag == 1)
                {
                printf("You open the door.\n");
                outflag = 2;
                goto restart;
                }
    if(roomnum == 3)
         {
          printf("There are no doors in the bathroom to open.\n");
          goto restart;
         }
            else
                {
                printf("The door is already open.\n");
                goto restart;
                }
            case(18):
            if(trunkop == 1)
                {
                printf("\nYou open the trunk.  You see some old clothes in it.\n");
                for(i = 0; i < NUMNOUN;i++)
                    {
                    if(obloc[roomnum][i] == NUTHIN)
                        {
                        obloc[roomnum][i] = 21;
                        break;
                        }
                    }
                goto restart;
                }
            else
                {
                printf("\nYou can't open the trunk. It seems to be locked.\n");
                break;
                }
            default:
        printf("\nThere is nothing you can open in %s.\n", nouns[nounum]);
                }
            break;

/* wear */  case(19):
    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

            switch(nounum)
            {
        case(14):
            if(seeit(nounum, roomnum, obloc) != NUTHIN)
                {
                printf("You put the scarf around your neck.\n");
                wearscarf = 1;
                for(i = 0; i < NUMNOUN; i++)
                    {
                    if(obloc[roomnum][i] == 14)
                        {
                        obloc[roomnum][i] = NUTHIN;
                        break;
                        }
                    }
                }

            if(carryit(nounum, carry) != NUTHIN)
                {
                printf("You put the scarf around your neck.\n");
                wearscarf = 1;
                for(i = 0; i < NUMCARRY; i++)
                    {
                    if(carry[i] == 14)
                        {
                        carry[i] = NUTHIN;
                        break;
                        }
                    }
                }
            break;
        case(31):
            if(seeit(nounum, roomnum, obloc) != NUTHIN)
                {
                wearboots = putboots();
                health--;
                for(i = 0; i < NUMNOUN; i++)
                    {
                    if(obloc[roomnum][i] == 31)
                        {
                        obloc[roomnum][i] = NUTHIN;
                        break;
                        }
                    }
                }

            if(carryit(nounum, carry) != NUTHIN)
                {
                wearboots = putboots();
                health--;
                for(i = 0; i < NUMCARRY; i++)
                    {
                    if(carry[i] == 31)
                        {
                        carry[i] = NUTHIN;
                        break;
                        }
                    }
                }
            break;
        case(21):
            if(seeit(nounum, roomnum, obloc) != NUTHIN)
                {
                printf("You put on the old clothes.\n");
                wearem = 1;
                for(i = 0; i < NUMNOUN; i++)
                    {
                    if(obloc[roomnum][i] == 21)
                        {
                        obloc[roomnum][i] = NUTHIN;
                        break;
                        }
                    }
                }

            if(carryit(nounum, carry) != NUTHIN)
                {
                printf("You put on the old clothes.\n");
                wearem = 1;
                for(i = 0; i < NUMCARRY; i++)
                    {
                    if(carry[i] == 21)
                        {
                        carry[i] = NUTHIN;
                        break;
                        }
                    }
                }
            break;
        case(32):
             if(seeit(nounum, roomnum, obloc) != NUTHIN)
                {
                printf("You put on the bracelet.  While doing so you poke yourself\n");
                printf("several times with the small sharp teeth.\n");
                wearneck = 1;
                health = health - 3;
                for(i = 0; i < NUMNOUN; i++)
                    {
                    if(obloc[roomnum][i] == 32)
                        {
                        obloc[roomnum][i] = NUTHIN;
                        break;
                        }
                    }
                }

            if(carryit(nounum, carry) != NUTHIN)
                {
                printf("You put on the bracelet.  While doing so you poke yourself\n");
                printf("several times with the small sharp teeth.\n");
                wearneck = 1;
                health = health - 3;
                for(i = 0; i < NUMCARRY; i++)
                    {
                    if(carry[i] == 32)
                        {
                        carry[i] = NUTHIN;
                        break;
                        }
                    }
                }
            break;
        case(22):
            if(seeit(nounum, roomnum, obloc) != NUTHIN)
                {
                printf("You put on the wig.\n");
                wearwig = 1;
                for(i = 0; i < NUMNOUN; i++)
                    {
                    if(obloc[roomnum][i] == 22)
                        {
                        obloc[roomnum][i] = NUTHIN;
                        break;
                        }
                    }
                }

            if(carryit(nounum, carry) != NUTHIN)
                {
                printf("You put on the wig.\n");
                wearwig = 1;
                for(i = 0; i < NUMCARRY; i++)
                    {
                    if(carry[i] == 22)
                        {
                        carry[i] = NUTHIN;
                        break;
                        }
                    }
                }
            break;
            default:
        printf("You can't wear %s in this game.\n",nouns[nounum]);
        printf("You can try it at home on your own though.\n");
            }
            break;

/* clean */ case(20):
    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

            switch(nounum)
                {
                case(16):
                    if(roomnum == 11)
                        {
                        if((carryit(14, carry) != NUTHIN) || wearscarf == 1)
                            {
                            printf("You wipe the dust and grime from the mirror with the scarf.\n");
                            mirclean = 1;
                            goto restart;
                            }
                        else
                            {
                            printf("You don't have anything to clean it with.\n");
                            goto restart;
                            }
                        }
                    else
                        {
                        printf("The mirror isn't here to clean.\n");
                        goto restart;
                        }
                default:
                printf("You clean %s. It looks a bit better. Don't you feel good now?\n", nouns[nounum]);
                }
            break;

/* eat */   case(21):
    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

            switch(nounum)
                {
                case(25):

    if(seeit(nounum,roomnum,obloc) != NUTHIN)
        {
        cakekey = eatit();
        health = health -6;
        for(i = 0; i < NUMNOUN; i++)
            {
            if(obloc[roomnum][i] == 25)
            obloc[roomnum][i] = NUTHIN;
            }
                break;
        }

    if(carryit(nounum,carry) != NUTHIN)
        {
        cakekey = eatit();
        health = health - 6;
        for(i = 0; i < NUMCARRY; i++)
            {
            if(carry[i] == 25)
            carry[i] = NUTHIN;
            }
                break;
        }
                default:
printf("You can eat some gross stuff in this game but you can't eat that.\n");
                }
            break;

/* drink */ case(22):
    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

            if(carryit(15,carry) != NUTHIN)  /* if you have the goblet */
                {
                switch(nounum)
                    {
                    case(40):
                    printf("You drink the white mouldy liquid.  It tastes so bad that you\n");
                    printf("immediately spit out the small amount in your mouth.\n");
                    printf("Unfortunately for you, a small amount trickles down your\n");
                    printf("throat.  It is enough to kill you.  You die immediately.\n");
                    exit(0);
                    }
                }
            printf("There is only one thing to drink in this game and that ain't it.\n");
            break;

/* help */  case(23):
            if(nounum == NUTHIN)
                {
    printf("\nHere is some general help:\n");
printf("This game understands only lower case.\n");
printf("Don't capitalize anything (except 'Pong')!\n");
printf("Some but not all of the verbs that I know are: get, drop, go,\n");
printf("read, examine, unlock, cut, snuff (i.e. snuff the candle), \n");
printf("wear, clean, say, open, eat, drink, look, light, quit, remove.\n");
printf("'health' will give you your health status.  Check it occaisionally.\n");
printf("There are lots of ways for your health status to go down.\n");
printf("If your health gets down to 0 then you are dead and the game is over.\n");
printf("'turn' will tell you how many turns you have taken so far.\n");
printf("'have' will tell you what you are carrying.\n");
printf("'quit' will give you a chance to exit the game.\n");
printf("Describe things EXACTLY.  If you can see 'the slimy green slug'\n");
printf("'get the slimy green slug' will work, but 'get the slug' will NOT.\n");
printf("Single letter abbreviations will work for moving in particular\n");
printf("directions.  Try 'e' if you want to 'go east', etc.\n");
/*
printf("If you are carrying an object, or can see an object, then try 'help the thing'. You\n");
printf("may get some extra help.  Don't try this unless you are really stuck!\n");
*/
                goto restart;
                }

            if(seeit(nounum, roomnum, obloc) != NUTHIN)
                {
                helproom(nounum);
                goto restart;
                }

            if(carryit(nounum, carry) != NUTHIN)
                {
                helpcarry(nounum);
                goto restart;
                }

        printf("Sorry, I can't help you with that right now.\n");
        break;
/* look */  case(24):               /* this is intercepted in in the */
            switch(nounum)          /* one verb section and sent to  */
                {                   /* descriptions(roomnum)         */
                default:
                    printf("in 24 'look' DEFAULT\n");
                }
            break;

/* quit */  case(25):
            printf("Do you want to quit?\n");
            printf("If you do then type 'y'. Anything else continues the game.\n");
            getit(answer);
            if(answer[0] == 121)
            exit(0);
            else
            goto restart;
/* vacuum */ case(26):
    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

            if(seeit(nounum,roomnum,obloc) == NUTHIN)
                {
                printf("You can't vacuum that right now.  This is definitely something\n");
                printf("you can try at home though.\n");
                goto restart;
                }
            if(carryit(19,carry) == NUTHIN)  /* can't vacuum if not carrying the vacuum */
                {
                printf("You can't vacuum anything right now because you don't have the vacuum.");
                goto restart;
                }
              switch(nounum)
                {
                case(17):
printf("You turn on the vacuum and try to vacuum the dust.  Unfortunately,\n");
printf("the vacuum blows the dust into great clouds in the room.  It gets\n");
printf("into your eyes and burns.  You inhale some and start to cough.  Through\n");
printf("your tears and coughs you finally manage to turn off the SuckBuster.\n");
printf("You cough, wheeze and spit phlegm for another ten minutes.\n");
                health = health -4;
                goto restart;
                default:
                printf("You vacuum the %s for a while.  Nothing interesting happens.\n",nouns[nounum]);
                goto restart;
                }


/* cut */ case(27):
    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

    for(i = 0; i < NUMCARRY;i++)
    {
    if(carry[i] == 23)  /* if you have the knife  */
        {
        if(nounum == 12)
        {
        if((k = seeit(nounum, roomnum, obloc)) != NUTHIN)
            {
            obloc[roomnum][k] = cut(nounum); /* piece of cake is in room */
            health = health - 17;
            scratches = 1;
            goto restart;
            }
        if((k = carryit(nounum, carry)) != NUTHIN)
            {
            carry[k] = cut(nounum); /* 'piece of cake' is carried */
            health = health - 17;
            scratches = 1;
            goto restart;
            } /* 4 */
        else
            {
            printf("The cake isn't here. You can't cut it if it isn't here.\n");
            goto restart;
            }
            }/* 3 */
        else
        {
        printf("You cut %s. Nothing happens.\n",nouns[nounum]);
        goto restart;
        }
        }/* 2 */
    }/* 1 */
printf("You don't have anything to cut %s with.\n",nouns[nounum]);
    break;

/* say */case(28):
    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

            if(nounum == 26) /* igot tago */
                {
                printf("You say 'igot tago'.  Your stomach drops to your feet\n");
                printf("and rises to your throat.  Everything is dark.\n");
                roomnum = 3;
                if((k = seeit(13,roomnum,obloc)) != NUTHIN) /* if wizard is here */
                    {
                    health = health - 10;
                    roomnum = brbye();
                    }
                }
            else
                {
                printf("You say '%s'.  Nothing interesting or useful happens.\n",secwrd);
                }
         break;
/* puke */  case(29):
            if(puke == 0 && roomnum == 3 && cakekey == 1)
                {
                printf("You puke into the small sink.\n");
                for(i = 0; i < NUMNOUN; i++)
                    {
                    if(obloc[roomnum][i] == NUTHIN)
                        {
                        obloc[roomnum][i] = 24; /* the puke is now in the sink */
                        break;
                        }
                    }
                goto restart;
                }
            printf("You try to puke, but surprisingly, you can't.\n");
            break;

/* flush */ case(30):
    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

        if(nounum == 28 && roomnum == 3)
            {
            printf("You flush the toilet.  Of course, you are standing in it.\n");
            printf("Down you go with the brown water, and the brown lumps that are in it.\n");
            printf("You land with a heavy thud.  The water and lumps shower down on you.\n");
            printf("Battered and bruised, spitting brown liquid, you struggle to your feet.\n");
            light = 0;
            roomnum = 11;
            stink = 1;
            health = health - 13; /* lose 13 health for the fall */
            goto restart;
            }
        else
            {
            printf("There is no flushing possible here!\n");
            goto restart;
            }
/* snuff */ case(31):
    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

        if(nounum == 1)
            {
            if(light == 1)
                {
                light = 0;
                printf("You put the candle out.  It gets darker.\n");
                goto restart;
                }
            else
                {
            printf("The candle isn't lit.  You can't snuff it.\n");
                goto restart;
                }
            }
        else
            {
            printf("The only thing you can snuff is the candle.\n");
            printf("You can't snuff %s.\n",nouns[nounum]);
            goto restart;
            }
/* remove */    case(32):
    if(nounum == NUTHIN)
        {
        nonoun(verbnum,verbs);
        goto restart;
        }

            if(nounum == 21 && wearem == 1)
                {
                wearem = 0;
                printf("You remove the old clothes.\n");
                printf("You drop them on the floor.\n");
                printf("Your mother rolls over in her grave.\n");
                for(k = 0; k < NUMNOUN; k++)
                    {
                    if(obloc[roomnum][k] == NUTHIN)
                        {
                        obloc[roomnum][k] = nounum;
                        goto restart;
                        }
                    }
                }
            if(nounum == 31 && wearem == 1)
                {
                wearboots = 0;
                printf("You remove the small white boots.\n");
                printf("You drop them on the floor.\n");
                printf("Your mother rolls over in her grave.\n");
                for(k = 0; k < NUMNOUN; k++)
                    {
                    if(obloc[roomnum][k] == NUTHIN)
                        {
                        obloc[roomnum][k] = nounum;
                        goto restart;
                        }
                    }
                }
            if(nounum == 14 && wearscarf == 1)
                {
                wearscarf = 0;
                printf("You remove the scarf from around your neck.\n");
                printf("You drop it on the floor.\n");
                printf("Your mother rolls over in her grave.\n");
                for(k = 0; k < NUMNOUN; k++)
                    {
                    if(obloc[roomnum][k] == NUTHIN)
                        {
                        obloc[roomnum][k] = nounum;
                        goto restart;
                        }
                    }
                }
            if(nounum == 22 && wearwig == 1)
                {
                wearwig = 0;
                printf("You remove the wig.\n");
                printf("You drop it on the floor.\n");
                printf("Your mother rolls over in her grave.\n");
                for(k = 0; k < NUMNOUN; k++)
                    {
                    if(obloc[roomnum][k] == NUTHIN)
                        {
                        obloc[roomnum][k] = nounum;
                        goto restart;
                        }
                    }
                }
            if(nounum == 32 && wearneck == 1)
                {
                wearneck = 0;
                printf("You remove the bracelet.\n");
                printf("You drop it on the floor.\n");
                health = health - 3;
                for(k = 0; k < NUMNOUN; k++)
                    {
                    if(obloc[roomnum][k] == NUTHIN)
                        {
                        obloc[roomnum][k] = nounum;
                        goto restart;
                        }
                    }
                }
            else
                {
printf("You can't remove %s cuz you aren't wearing it.\n",nouns[nounum]);
                goto restart;
                }

    default:
    printf("default for verbs: you should never see this line.\n");

        }
    goto restart;
}


setup()
    {
printf("\nBeta version -- for test purposes only -- bound to buggy!\n");
printf("If you find bugs, or have suggestions to improve this game, please\n");
printf("let me know.  All suggestions will be seriously considered.\n");
printf("Send e-mail to me directly on MindLink! or I can be reached\n");
printf("on the internet at Bill_Moore@mindlink.bc.ca\n");
printf("Copyright 1993 by Bill Moore.  This program may be distributed\n");
printf("for free, but it may not be sold, rented, leased, etc.\n");
printf("\nYou are standing on the porch of an abandoned two story house.\n");
printf("The day is cold and windy. The sun is just setting and it \n");
printf("throws your shadow ahead of you onto the door of the house.\n");
printf("You are an adventurous person and you would like to see what is\n");
printf("inside the house. The house does look a bit scary. You stand and\n");
printf("stare at the house and think it over.\n");
printf("Your shadow partially darkens a sign that says:\n");
printf("Welcome to the Gross Residence!\n");
    }

descriptions(roomnum)
int roomnum;
    {
    switch(roomnum)
        {
        case(0):
printf("There is rotting food scattered about.  Much of it is\n");
printf("growing pale yellowish mold that is waving gently.  Some of the tendrils \n");
printf("reach out to you with a caressing motion, as if to stroke your cheek.\n");
        break;

        case(1):
printf("There are many broken dishes and dried food is splattered on the wall.\n");
printf("There are some small rat carcasses on the plates. They are mostly\n");
printf("picked clean.\n");
        break;

        case(2):
printf("At first you see a number of books scattered about in this room.\n");
printf("It looks as if someone has ransacked it searching for something.\n");
printf("Then, you see a ghostly figure in robes and a conical hat moving from\n");
printf("one book to another, leafing through it and then throwing it down in\n");
printf("apparent disgust, only to grab another and do the same thing.\n");
        break;

        case(3):
printf("You notice (actually you can't help but notice) that you are in\n");
printf("a very small room.  The room has four walls but no doorway.\n");
printf("You are standing in the only available space: the toilet.\n");
printf("Your feet are cold because you are standing in brown liquid up to\n");
printf("your ankles.  Some of the brown liquid has run into your shoes.\n");
printf("There is a small sink attached to the wall at about waist height.\n");
printf("This room smells like the ten worst outhouses in the world.\n");
printf("Your stomach feels very queasy.  You feel like you might puke.\n");
                break;

        case(4):
printf("The windows are boarded over.  You peek between the boards, but\n");
printf("the windows are so dirty you cannot see much inside the house.\n");
        break;

        case(5):
printf("The entry hall is neat.  On the floor are clean, shiny, black\n");
printf("and white checkerboard tiles.  Standing here are several small\n");
printf("tables with narrow armless chairs next to them.\n");
        break;

        case(6):
printf("The doors are open.  The rooms beyond are dark.\n");
        break;

        case(7):
printf("Most of the mess seems to have been made with slime.\n");
        break;

        case(8):
printf("It is very dark.  You can hear something flying about\n");
printf("overhead, but it is too dark to see what it is.\n");
        break;

        case(9):
printf("A rat in the corner sneezes, sending up a small cloud of dust.\n");
printf("It squeaks and runs into a hole in the wall.\n");
        break;

        case(10):
printf("It is very dark here.  You can hear a scrabbling sound in the\n");
printf("walls, but you can't see what is making the sound.\n");
        break;

        case(11):
printf("You try not to breathe, but that doesn't work very well.\n");
        break;

        default:
printf("Default in descriptions(n).\n");
        break;
        };
}

examine(nounum, roomnum)
int nounum, roomnum;
    {
    switch(nounum)
        {
        case(0):
            printf("You see a box of large wooden kitchen matches.  They \n");
            printf("are RED DEVIL brand.  There is a picture of a smiling\n");
            printf("devil on the box with flames for eyes. Below the devil\n");
            printf("it says LIGHT ME UP!!\n");
            break;

        case(1):
            printf("You see a small stub of a candle.  It has a short wick and\n");
            printf("does not look like it would last very long.\n");
            break;
        case(2):
            printf("You see a small brass key.\n");
            break;
        case(3):
            printf("You see a rusty iron key.\n");
            break;
        case(4):
        switch(roomnum)
            {
            case(4):
        printf("You see a heavy wooden door.  It seems to be made of oak planks bound\n");
        printf("together with some rusty iron bands.  There is an iron doorknob and an\n");
        printf("iron lock plate below it. It seems very solid.  A small sign\n");
        printf("near the bottom of the door says:  Solicitors and Pedlars Welcome!\n");
            break;
            case(5):
        printf("You see a heavy wooden door.  It seems to be made of oak planks bound\n");
        printf("together with some tarnished silver bands.  There is a tarnished silver\n");
        printf("doorknob and lock plate.\n");
            break;
            default:
        printf("You see a door.  It is not interesting at all.\n");
            break;
            }
        break;
        case(5):
    printf("You see a silver key.\n");
            break;
        case(6):
    printf("You see a doormat.  It looks like it may have been made\n");
    printf("by weaving together dog tails.  You can recognize the\n");
    printf("tails of a Labrador retriever, a husky, and a St. Bernard.\n");
        break;
        case(7):
    printf("You see some bats.  They are black, have long sharp teeth\n");
    printf("and seem to be flying directly toward you.\n");
        break;
        case(12):
    printf("You see a cake.  At one time it may have been a birthday cake. \n");
    printf("You can make out\n\n");
    printf("          HAP Y 24 7th B RTHD Y\n");
    printf("          YGN  RT DSQ\n\n");
    printf("In the frosting are the tracks of small animals.  There are many\n");
    printf("small black specks on the cake.\n");
            break;
        case(13):
    printf("You see a ghostly wizard. He is pacing about the room\n");
    printf("in an agitated sort of way.  Sometimes the wizard stops\n");
    printf("and, holding his crotch, hops up and down for a moment\n");
    printf("before resuming his pacing.\n");
            break;
        case(14):
    printf("You see a plaid scarf.  It is green and purple with flecks of\n");
    printf("orange.  It has dried reddish brown stains on it.\n");
            break;
        case(15):
    printf("You see a goblet. It is difficult to tell what metal it may\n");
    printf("be made of.  Perhaps copper, as it is covered with a thick\n");
    printf("green verdigris.  In the bottom of the goblet is a milky white\n");
    printf("liquid with specks of pinkish mould floating on it.\n");
            break;
        case(16):
    printf("You see a mirror.  The surface of the mirror is so dirty that\n");
    printf("you cannot make out your reflection.\n");
            break;
        case(17):
    printf("You see some dust, made up mostly of dandruff and powdered snot.\n");
            break;
        case(18):
    printf("You see a trunk.  It is a solid wooden trunk with metal \n");
    printf("reinforcements.  It has a heavy brass padlock.\n");
            break;
        case(19):
    printf("You see a vacuum cleaner. It is a small battery operated\n");
    printf("SuckBuster.  A thick yellow-white liquid is oozing from a crack\n");
    printf("in the handle.\n");
            break;
        case(20):
    printf("You see a book.  The title is SOME USEFUL HOUSEHOLD SPELLS.\n");
            break;
        case(21):
    printf("You see some clothes.  They smell as if they have been here for a\n");
    printf("long time.  As you poke the clothes some bugs run from the\n");
    printf("pile and out through a small hole in the back of the trunk.\n");
        break;
        case(22):
    printf("You see a wig.  The hair is standing straight up.  Some large\n");
    printf("slugs appear to have been caught in the hair and died.  Small\n");
    printf("white worms are eating them.\n");
            break;
        case(23):
    printf("You see a knife.  It is a large kitchen knife with a serrated\n");
    printf("blade.  The handle is shiny with grease.  On the blade is written:\n");
    printf("        NINJA KNIFE\n");
    printf("     Cuts to the Bone!\n");
            break;
        case(24):
    printf("You notice the barely chewed remains of the piece of cake you ate earlier.\n");
    printf("You also see something faintly shining amongst the chunks of puke.\n");
    printf("A half of a worm is wiggling in the puke.\n");
            break;
        case(25):
    printf("You see a small piece of cake.  It may have half a worm in it.\n");
    printf("Certainly there was half a worm wriggling on the table.\n");
        break;
        case(27):
    printf("You see something faintly shining amidst the puke.\n");
        break;
        case(28):
    printf("You examine the toilet you are standing in.  It may once have been\n");
    printf("white, but is now covered in flecks of brown, yellow and red crud.  You\n");
    printf("do not admire the artistic pattern of these flecks, bits and chunks.\n");
        break;
        case(31):
    printf("You examine the small white boots.  They have cunning little red hearts\n");
    printf("around the top and a white tassel on the front.  You think they are\n");
    printf("great boots except they are several sizes too small.\n");
        break;
        case(32):
    printf("You see a bracelet made of very small and delicate skulls.  Perhaps\n");
    printf("they are shrew skulls.  The teeth in the little jaws are very sharp.\n");
        break;
        case(33):
    printf("The headline on the newspapers is: WAR!\n");
        break;
        case(34):
    printf("You examine the decomposing bat.  It is moist and rotting.\n");
    printf("Its head is missing.\n");
        break;
        case(35):
    printf("You see a large, black coal-burning stove.\n");
        break;
        case(36):
    printf("Looking at the garbage you see furry, rotting carrots, Dr. Caligari\n");
    printf("slug food cans, dying slugs, mummy windings, tissues with dried green\n");
    printf("ooze, cancerous beetles, phlegm bags, enough maggots to feed your\n");
    printf("pet dung lizard for weeks, and some snot straws.\n");
        break;
        case(37):
    printf("You examine the Pong game.  This particular unit is signed\n");
    printf("by Nolan Bushnell.  Fascinated, you manoeuver the tiny\n");
    printf("blip around the screen.\n");
        break;
        case(38):
    printf("You see a long wooden porch. There are holes in several places where\n");
    printf("the wood has rotted through.\n");
        break;
        case(39):
    printf("These rats are dark grey.  They have, of course, long sharp teeth and\n");
    printf("long sharp pointed hairless tails.  They sit up on their hind legs and\n");
    printf("hiss at you.\n");
        break;

        default:
    printf("You examine the object, but don't see anything interesting.\n");
        }
    }

knock(nounum, roomnum)
int nounum;
int roomnum;
    {
    switch(nounum)
        {
    case(4):
        if(roomnum == 4)
            {
printf("You hear a faint whispery sort of voice say,\n");
printf("Come in little person.  We would like to have fun with you.\n");
            break;
            }
        if(roomnum == 5)
            {
printf("A very loud and eager voice says:,\n");
printf("Now we've got you little person and we are going to keep you forever...\n");
printf("You hear something laughing above you, and a bit of drool drips\n");
printf("onto your hand.  You wipe it on your pants as fast as you can.\n");
            break;
            }
printf("You hear the sound of your knuckles on the door.  Nothing happens.\n");
        break;
    default:
    printf("default in knock()\n");
    }
}



/*
-- useful prose:

1.  printf("That is not one of the things that you can examine in this\n");
    printf("game.  Knowing more about it will not help you get out of the\n");
    printf("house.  Some people find it rewarding to imagine this thing\n");
    printf("more fully.  Feel free to do so now.\n");
*/

helpcarry(nounum)
int nounum;
    {
    switch(nounum)
        {
        case(0):
        printf("in helpcarry() case(0).\n");
        break;
        default:
        printf("in helpcarry() default.\n");
        }
}

helproom(nounum)
int nounum;
    {
    switch(nounum)
        {
        case(0):
        printf("in helproom() case(0).\n");
        break;
        default:
        printf("in helproom() default.\n");
        }
}

int cut(nounum)
int nounum;
    {
    switch(nounum)
        {
        case(12):
    printf("You hold the cake and try to cut it. The icing is rock hard.  You saw at\n");
    printf("one corner of the cake with the knife.  The icing suddenly gives way\n");
    printf("as the greasy handle of the knife slips in your right hand.\n");
    printf("You cut a piece off the cake, a piece off your left thumb and knock\n");
    printf("the body of the cake and the bit of your thumb off the table.\n");
    printf("A small, sharp-toothed lizard dashes out of the shadows and snaps\n");
    printf("up the bit of your thumb.  Half of a large worm wriggles out of the\n");
    printf("piece of cake and onto the table.  You watch, frozen with fascination\n");
    printf("and disgust as it twists and contorts itself on the table, moving\n");
    printf("closer to the edge.  Finally it falls to the floor.  The lizard\n");
    printf("snaps up the half worm and, apparently  disoriented, runs up your\n");
    printf("pants leg.  You are frozen no more.  Very, very quickly you tear\n");
    printf("your pants off, but not before the lizard's sharp claws and teeth\n");
    printf("inflict several painful gashes on your legs.  The lizard seems to\n");
    printf("like the pants you have so quickly removed.  It sits in them and\n");
    printf("hisses at you.  You decide to leave your pants with the lizard.\n");
        return(25);
        }
    }

readit(nounum)
int nounum;
    {
    switch(nounum)
        {
        case(20):
    printf("In large block letters you read:\n");
    printf("IF YOU CAN'T WAIT AND ARE DESPERATE TRY igot tago\n");
        break;
        case(33):
    printf("The headline is:\n");
    printf("      WAR!\n");
    printf("It covers the entire front page.\n");
        break;
        }
    }

int carryit(nounum, carry)
int nounum;
int carry[NUMCARRY];
    {
    int k;
    for(k = 0; k < NUMCARRY; k++)
        {
        if(nounum == carry[k])
            {
            return(k);
            }
        }
    return(-1);
    }
/*
carryit() checks to see if you are carrying the object you want to do
something to.  It returns k (LOGICAL TRUE) if you have it.  You can use
this value to designate where the object is in the array.  Otherwise it
returns -1 (NUTHIN) if you aren't carrying the object
*/

int seeit(nounum, roomnum, obloc)
int nounum, roomnum;
int obloc[NUMROOM][NUMNOUN];
    {
    int k;
    for(k = 0; k < NUMNOUN; k++)
        {
        if(nounum == obloc[roomnum][k])
            {
            return(k);
            }
        }
    return(-1);
    }
/*
seeit() checks to see if the object you want to do something to is in
the room.  It returns k (LOGICAL TRUE any value other than -1 is true)
if it is.  The k can be used
to designate where the object is in the array.  Otherwise it returns
-1 (NUTHIN) if you can't see the object.
*/

byebye()
    {
    printf("The wizard pauses for a moment as he notices that you\n");
    printf("are standing there staring at him with your mouth open.\n");
    printf("He gestures with his left hand and seems to say something,\n");
    printf("although you can't quite hear what he says.\n");
    printf("The scene in front of you fades as an odd feeling\n");
    printf("comes over you. You find yourself sitting in the living\n");
    printf("room of this house staring at an old Pong game with your mouth open.\n");
    return(9);
}

death(turn)
int turn;
    {
    printf("\nA lot of bad stuff has happened to your body:\n");
    printf("The small sharp toothed lizard has scratched your legs\n");
    printf("and bit some tender areas.\n");
    if(turn > 200)
        {
        printf("These bites and scratches have become infected and are suppurating.\n");
        }
    printf("You have been flushed.  The fall battered your body and you swallowed\n");
    printf("some of the brown water with nasty germs in it.\n");
    printf("The bats have bitten your face and head.\n");
    printf("The rats have bitten your ankles.\n");
    printf("Unfortunately, you can't live with this.  You have died.\n\n");
    exit(0);
    }

healthy(health)
int health;
    {
    printf("You are %d percent healthy.\n",health);
    }

brbye()
    {
    printf("\a\nThe wizard is seated on the toilet.\n");
    printf("He pauses for a moment as he notices that you\n");
    printf("are standing there staring at him with your mouth open.\n");
    printf("He gestures with his left hand and seems to say something,\n");
    printf("although you can't quite hear what he says.\n");
    printf("The scene in front of you fades as an odd feeling\n");
    printf("comes over you. You find yourself sitting in the \n");
    printf("living room staring at an old Pong game.  Your mouth\n");
    printf("is still open.\n");
    return(9);
}

putboots()
    {
    printf("You put the small white boots on your feet.  You have to\n");
    printf("jam your feet into them.  This hurts your toes.\n");
    return(1);
    }

eatit()
    {
    printf("You put the small piece of the cake in your mouth.\n");
    printf("The taste makes you gag.  You chew once, but you feel\n");
    printf("something wiggly against your tongue so you swallow\n");
    printf("quickly.  As the piece of cake goes down you feel a small\n");
    printf("hard object stick in your throat.  You cough and\n");
    printf("sputter, and finally you swallow the whole thing.\n");
    return(1);
    }

wonit(health,turn)
int health, turn;
    {
    printf("As well as you can with your injuries, you step out onto the porch\n");
    printf("and inhale the sweet night air.  You cough and sputter once more.\n");
    printf("You puke onto the porch steps.  Vomit beetles scury toward the feast.\n");
    printf("Congratulations!!  You have won the game.!!\n");
    printf("It has taken you %d turns and you are still %d per cent healthy.\n", turn, health);
    printf("This is a fine achievement!  You bask in your glory for a few\n");
    printf("moments before you walk down the steps and head home.\n");
    printf("Be careful you don't slip in the puke!\n");
    }

char *
getit(buf)
    char *buf;
{
    register int c;
    register char *s;

    for(s = buf; (c = getchar()) != '\n';)
        if(c == EOF)
            if(s == buf)
                return(NULL);
            else
                break;
        else
            *s++ = c;
    *s = 0;
    return(buf);
}

int nonoun(verbnum,verbs)
int verbnum;
char *verbs[NUMVERB];

    {
    printf("You have to %s SOMETHING.  Try to be more specific.\n",verbs[verbnum]);
    return 0;
    }
