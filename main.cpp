#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > AdjacentMatrix; //Organized such that the ith element corresponds to the ith row in the matrix
int BiggestMatrix;
int Intro()//a nice little intro msg, and all the UI for the program
{
    cout << "Please type the integer indicating the highest nxn adjacent matrix you want the rank of.\n";
    cout << "(Must be an integer greater than or equal to two)" << endl;
    if (cin >> BiggestMatrix)
        return 0;
    else if (cin.bad() || cin.eof())
        return -1;
    else
        return -2;

}

vector<int> Add(vector<int>& a, vector<int>& b)
{
    assert(a.size() == b.size());
    vector<int> Output;
    for (int i = 0; i < a.size(); i++)
    {
        if ((a[i] == 0 && b[i] == 0) || (a[i] == 1 && b[i] == 1))
            Output.push_back(0);
        else
            Output.push_back(1);
    }
    return Output;
}


void RowReduce(vector<vector<int> >& Input)
{

    //we know that there is all 1's along the main diag. of the adjacent amtrix no matter what
    //So now it's just a matter of row reducing

//        for (int i = 0; i < Input.size(); i++)
//        {
//            for (int j = 0; j < Input.size(); j++)
//            {
//                if (i == j && Input[i][j] == 1)
//                {
//
//                }
//            }
//        }
//        return rank;
        for (int collnumber = 0; collnumber < Input.size(); collnumber++)
        {
            for (int i = collnumber+1; i < Input.size(); i++)
            {
                if (Input[i][collnumber] == 1)
                {
                    auto InputAtI = Input[i];
                    auto InputAtCollNumber = Input[collnumber];
                    Input[i] = InputAtCollNumber;
                    Input[collnumber] = InputAtI;
                }
            }

            for (int i = 0; i < Input.size(); i++)
            {
                if (Input[i][collnumber] == 1 && i != collnumber)
                {
                    Input[i]= Add(Input[collnumber],Input[i]);
                }
            }
        }


}

int Rank(vector<vector<int> >& input)
{
    int rank = 0;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i][i] == 1)
            rank++;
    }
    return rank;
}

int main()
{
    /*Take input*/
    if (int ret = Intro(); ret != 0)
        exit(ret);

    /*One more quick error check*/
    if (BiggestMatrix < 2)
    {
        cout << "Please enter a number greater than or equal to 2!" << endl;
        exit(-3);
    }

    for (int BoardSize = 2; BoardSize<=BiggestMatrix; BoardSize++) //Will have to loop through each matrix starting with a 2x2 board...
    {

         //Create the board...

        vector<vector<int> > Board; //Same organization as AdjacentMatrix.

        for (int i = 1; i<=BoardSize; i++)//i is the number of rows we've gone through so far
        {
            //Create the "square/box numbers" for this row
            vector<int> ThisRow;

            /*
             * This "startnumber" "endnumber" buisness is just to ensure we will input the correct
             * box number in each entry in the board.
             */

            int StartNumber = 1+BoardSize*(i-1);
            int EndNumber = StartNumber+(BoardSize-1);

            for (int j = StartNumber; j<=EndNumber; j++)
            {
                ThisRow.push_back(j);
            }
            Board.push_back(ThisRow);
        }

        /*Board has now been built*/

        //Systamtically go through each entry in board and make a row for our adjacent matrix...
        for (int i = 0; i < BoardSize; i++)
        {
            for (int j = 0; j < BoardSize; j++)
            {
                /*
                 * There are three options... either:
                 *
                 * A: the cell being investigated is a corner spot
                 * B: A wall piece
                 * C: a cneter piece
                 *
                 * We test for those...
                 */
                bool isTopLeftCorner = false;
                bool isTopRightCorner = false;
                bool isBottomLeftCorner = false;
                bool isBottomRightCorner = false;


                if ( (i == 0) && (j == 0) )
                {
                    isTopLeftCorner= true;
                }
                else if ( (i==0) && (j == BoardSize-1) )
                {
                    isTopRightCorner = true;
                }
                else if ( (i==BoardSize-1) && (j == 0) )
                {
                    isBottomLeftCorner = true;
                }
                else if ( (i==BoardSize-1) && (j == BoardSize-1) )
                {
                    isBottomRightCorner = true;
                }

                if (isBottomLeftCorner == false && isBottomRightCorner == false && isTopLeftCorner == false && isTopRightCorner == false)//not a corner :(
                {
                    //Maybe it's a boarder piece..
                    if (i == 0)//Top boarderpiece
                    {
                        vector<int> EntrysToBeOne;
                        bool IsOne = false;
                        vector<int> ThisRow;

                        EntrysToBeOne.push_back(Board[i][j]-1);
                        EntrysToBeOne.push_back(Board[i][j]);
                        EntrysToBeOne.push_back(Board[i][j]+1);
                        EntrysToBeOne.push_back(Board[i][j]+BoardSize);

                        for (int k = 0; k < BoardSize; k++)
                        {
                            for (int l = 0; l < BoardSize; l++)
                            {
                                for (int index = 0; index < EntrysToBeOne.size(); index++)
                                {
                                    if (Board[k][l] == EntrysToBeOne[index])
                                    {
                                        IsOne=true;
                                        break;
                                    }
                                }

                                if (IsOne == true)
                                {
                                    ThisRow.push_back(1);
                                }
                                else
                                    ThisRow.push_back(0);
                                IsOne=false;
                            }
                        }
                        AdjacentMatrix.push_back(ThisRow);
                    }
                    else if (j == 0)//Left side boarder piece.
                    {
                        vector<int> EntrysToBeOne;
                        bool IsOne = false;
                        vector<int> ThisRow;

                        EntrysToBeOne.push_back(Board[i][j]-BoardSize);
                        EntrysToBeOne.push_back(Board[i][j]);
                        EntrysToBeOne.push_back(Board[i][j]+1);
                        EntrysToBeOne.push_back(Board[i][j]+BoardSize);

                        for (int k = 0; k < BoardSize; k++)
                        {
                            for (int l = 0; l < BoardSize; l++)
                            {
                                for (int index = 0; index < EntrysToBeOne.size(); index++)
                                {
                                    if (Board[k][l] == EntrysToBeOne[index])
                                    {
                                        IsOne=true;
                                        break;
                                    }
                                }

                                if (IsOne == true)
                                {
                                    ThisRow.push_back(1);
                                }
                                else
                                    ThisRow.push_back(0);
                                IsOne=false;
                            }
                        }
                        AdjacentMatrix.push_back(ThisRow);

                    }
                    else if (j ==BoardSize-1)//Right side boarder piece
                    {
                        vector<int> EntrysToBeOne;
                        bool IsOne = false;
                        vector<int> ThisRow;

                        EntrysToBeOne.push_back(Board[i][j]-BoardSize);
                        EntrysToBeOne.push_back(Board[i][j]-1);
                        EntrysToBeOne.push_back(Board[i][j]);
                        EntrysToBeOne.push_back(Board[i][j]+BoardSize);


                        for (int k = 0; k < BoardSize; k++)
                        {
                            for (int l = 0; l < BoardSize; l++)
                            {
                                for (int index = 0; index < EntrysToBeOne.size(); index++)
                                {
                                    if (Board[k][l] == EntrysToBeOne[index])
                                    {
                                        IsOne=true;
                                        break;
                                    }
                                }

                                if (IsOne == true)
                                {
                                    ThisRow.push_back(1);
                                }
                                else
                                    ThisRow.push_back(0);
                                IsOne=false;
                            }
                        }
                        AdjacentMatrix.push_back(ThisRow);
                    }
                    else if (i==BoardSize-1)//Bottom boarder piece...
                    {
                        vector<int> EntrysToBeOne;
                        bool IsOne = false;
                        vector<int> ThisRow;

                        EntrysToBeOne.push_back(Board[i][j]-BoardSize);
                        EntrysToBeOne.push_back(Board[i][j]-1);
                        EntrysToBeOne.push_back(Board[i][j]);
                        EntrysToBeOne.push_back(Board[i][j]+1);

                        for (int k = 0; k < BoardSize; k++)
                        {
                            for (int l = 0; l < BoardSize; l++)
                            {
                                for (int index = 0; index < EntrysToBeOne.size(); index++)
                                {
                                    if (Board[k][l] == EntrysToBeOne[index])
                                    {
                                        IsOne=true;
                                        break;
                                    }
                                }

                                if (IsOne == true)
                                {
                                    ThisRow.push_back(1);
                                }
                                else
                                    ThisRow.push_back(0);
                                IsOne=false;
                            }
                        }
                        AdjacentMatrix.push_back(ThisRow);
                    }
                    else//a center piece
                    {
                        vector<int> EntrysToBeOne;
                        bool IsOne = false;
                        vector<int> ThisRow;

                        EntrysToBeOne.push_back(Board[i][j]-BoardSize);
                        EntrysToBeOne.push_back(Board[i][j]-1);
                        EntrysToBeOne.push_back(Board[i][j]);
                        EntrysToBeOne.push_back(Board[i][j]+1);
                        EntrysToBeOne.push_back(Board[i][j]+BoardSize);

                        for (int k = 0; k < BoardSize; k++)
                        {
                            for (int l = 0; l < BoardSize; l++)
                            {
                                for (int index = 0; index < EntrysToBeOne.size(); index++)
                                {
                                    if (Board[k][l] == EntrysToBeOne[index])
                                    {
                                        IsOne=true;
                                        break;
                                    }
                                }

                                if (IsOne == true)
                                {
                                    ThisRow.push_back(1);
                                }
                                else
                                    ThisRow.push_back(0);
                                IsOne=false;
                            }
                        }
                        AdjacentMatrix.push_back(ThisRow);
                    }

                }
                else//is a corner
                {
                    if (isTopLeftCorner)
                    {
                        vector<int> EntrysToBeOne;
                        bool IsOne = false;
                        vector<int> ThisRow;

                        EntrysToBeOne.push_back(Board[i][j]);
                        EntrysToBeOne.push_back(Board[i][j]+1);
                        EntrysToBeOne.push_back(Board[i][j]+BoardSize);

                        for (int k = 0; k < BoardSize; k++)
                        {
                            for (int l = 0; l < BoardSize; l++)
                            {
                                for (int index = 0; index < EntrysToBeOne.size(); index++)
                                {
                                    if (Board[k][l] == EntrysToBeOne[index])
                                    {
                                        IsOne=true;
                                        break;
                                    }
                                }

                                if (IsOne == true)
                                {
                                    ThisRow.push_back(1);
                                }
                                else
                                    ThisRow.push_back(0);
                                IsOne=false;
                            }
                        }
                        AdjacentMatrix.push_back(ThisRow);
                    }
                    else if (isTopRightCorner)
                    {
                        vector<int> EntrysToBeOne;
                        bool IsOne = false;
                        vector<int> ThisRow;

                        EntrysToBeOne.push_back(Board[i][j]-1);
                        EntrysToBeOne.push_back(Board[i][j]);
                        EntrysToBeOne.push_back(Board[i][j]+BoardSize);

                        for (int k = 0; k < BoardSize; k++)
                        {
                            for (int l = 0; l < BoardSize; l++)
                            {
                                for (int index = 0; index < EntrysToBeOne.size(); index++)
                                {
                                    if (Board[k][l] == EntrysToBeOne[index])
                                    {
                                        IsOne=true;
                                        break;
                                    }
                                }

                                if (IsOne == true)
                                {
                                    ThisRow.push_back(1);
                                }
                                else
                                    ThisRow.push_back(0);
                                IsOne=false;
                            }
                        }
                        AdjacentMatrix.push_back(ThisRow);
                    }
                    else if (isBottomLeftCorner)
                    {
                        vector<int> EntrysToBeOne;
                        bool IsOne = false;
                        vector<int> ThisRow;

                        EntrysToBeOne.push_back(Board[i][j]-BoardSize);
                        EntrysToBeOne.push_back(Board[i][j]);
                        EntrysToBeOne.push_back(Board[i][j]+1);

                        for (int k = 0; k < BoardSize; k++)
                        {
                            for (int l = 0; l < BoardSize; l++)
                            {
                                for (int index = 0; index < EntrysToBeOne.size(); index++)
                                {
                                    if (Board[k][l] == EntrysToBeOne[index])
                                    {
                                        IsOne=true;
                                        break;
                                    }
                                }

                                if (IsOne == true)
                                {
                                    ThisRow.push_back(1);
                                }
                                else
                                    ThisRow.push_back(0);
                                IsOne=false;
                            }
                        }
                        AdjacentMatrix.push_back(ThisRow);

                    }
                    else if (isBottomRightCorner)
                    {
                        vector<int> EntrysToBeOne;
                        bool IsOne = false;
                        vector<int> ThisRow;

                        EntrysToBeOne.push_back(Board[i][j]-BoardSize);
                        EntrysToBeOne.push_back(Board[i][j]-1);
                        EntrysToBeOne.push_back(Board[i][j]);

                        for (int k = 0; k < BoardSize; k++)
                        {
                            for (int l = 0; l < BoardSize; l++)
                            {
                                for (int index = 0; index < EntrysToBeOne.size(); index++)
                                {
                                    if (Board[k][l] == EntrysToBeOne[index])
                                    {
                                        IsOne=true;
                                        break;
                                    }
                                }

                                if (IsOne == true)
                                {
                                    ThisRow.push_back(1);
                                }
                                else
                                    ThisRow.push_back(0);
                                IsOne=false;
                            }
                        }
                        AdjacentMatrix.push_back(ThisRow);
                    }
                    else
                    {
                        cout << "This case should never happene ever! lol" << endl;
                    }
                }
            }
        }


//        cout << "Row reduced adjacent Matrix for a " << BoardSize << "x" << BoardSize << " board:" << endl;
//        RowReduce(AdjacentMatrix);
//        for (int k = 0; k < AdjacentMatrix.size(); k++)
//        {
//            for (int counter = 0; counter < AdjacentMatrix.size(); counter++)
//            {
//                cout << AdjacentMatrix[k][counter] << " ";
//            }
//            cout << "\n";
//        }
//        cout << "\n";
//        cout << "******" << endl;
//        cout << "\n";

        RowReduce(AdjacentMatrix);
        cout << "Board size: " << BoardSize << "x" << BoardSize << "   " "Rank of Adjacency Matrix: ";
        cout << Rank(AdjacentMatrix) << endl;
        AdjacentMatrix.clear();
    }//end of looping each matrix...

    return 0;
}
