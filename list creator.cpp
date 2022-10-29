#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>

using std::cout; using std::cin; using std::string; using std::vector; using std::to_string; using std::getline; using std::ws; using std::ifstream; using std::ofstream; using std::stoi;

/* 
* written by chapel1337
* started on 10/26/2022
* finished on 10/28/2022
* 
* didn't work on this on 10/27/2022 because i was working on a different project
* it's currently 11pm and i'm in a hotel room while typing this
* first try at multidimensional vectors, my most ambitious project yet™️
* 1040 lines, i've finally surpased the 1,000 line milestone!!!
*/

ofstream output{};
ifstream input{};

vector<vector<string>> listOfLists{};

vector<string> listNames{};
vector<vector<int>> listOfListsChecked{};

string currentListName{};
vector<int> currentListChecked{};
vector<string> currentList{};

// ------- \\

void returnTo(string returnFunction);

void clear()
{
#ifdef _WIN32
    system("cls");
#elif (__LINUX__)
    system("clear");
#endif
}

void pause()
{
    cout << "press any key to continue . . .\n";

    cin.get();
}

char ccin()
{
    string input{};
    std::getline(std::cin, input);

    return input[0];
}

void sleep(auto time)
{
    Sleep(time * 1000);
}

void beep()
{
    Beep(200, 325);
}

/*
void setTextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
*/

void title(string title)
{
    SetConsoleTitleA(("list creator - " + title).c_str());
}

void title()
{
    SetConsoleTitleA("list creator");
}

void title(string title, int i)
{
    SetConsoleTitleA(("list creator - " + title + to_string(i)).c_str());
}

void invalidInput(string message, string returnFunction)
{
    clear();
    title("invalid input");

    cout << "invalid input: " << message << '\n';

    sleep(2);
    returnTo(returnFunction);
}

// ------- \\

void displayLists()
{
    clear();

    // brackets hell
    cout << currentListName << " [current list]\n\n";

    for (int i{ 0 }; i < currentList.size(); ++i)
    {
        if (currentListChecked[i] == 1)
        {
            cout << i + 1 << ". " << currentList[i] << " [DONE]\n";
        }
        else
        {
            cout << i + 1 << ". " << currentList[i] << '\n';
        }
    }
    cout << "\n\n";

    for (int i{ 0 }; i < listOfLists.size(); ++i)
    {
        cout << listNames.at(i) << "\n\n";

        for (int o{ 0 }; o < listOfLists.at(i).size(); ++o)
        {
            if (listOfListsChecked[i][o] == 1) // not using .at(); for this
            {
                cout << o + 1 << ". " << listOfLists[i][o] << " [DONE]\n";
            }
            else
            {
                cout << o + 1 << ". " << listOfLists[i][o] << '\n';
            }
        }
        cout << "\n\n";
    }

    pause();
    returnTo("listSettings");
}

void addIndices()
{
    clear();
    title("add indices");

    bool finished{ false };

    while (!finished)
    {
        clear();

        string index{};
        string response{};

        cout << "input index: \n\n";

        cout << "> ";
        getline(cin >> ws, index);

        clear();

        currentList.push_back(index);
        currentListChecked.push_back(0);

        cout << "added " << index << " to list\n\n";
        cout << "> ";

        sleep(2);
        clear();

        cout << "would you like to continue to add indices?\n\n";

        cout << "> ";
        getline(cin >> ws, response);

        if (response == "no" || response == "n")
        {
            finished = true;
        }
    }

    returnTo("createList");
}

// ------- \\

/*
bool randomColorsEnabled{ false };

void toggleRandomColors()
{
    clear();
    title("random colors");

    if (randomColorsEnabled)
    {
        // excluding 0 because it's black (I Don't Mean What You're Thinking), the user won't be able to see the character
        setTextColor(getRandom(1, 15));

        cout << "enabled random colors\n";
    }
    else
    {
        resetTextColor();

        cout << "disabled random color\n";
    }

    sleep(2);
    returnTo("settings");
}
*/

// ------- \\

void setCurrentList()
{
    clear();
    title("set current list");

    int response{};
    string replaceResponse{};

    for (int i{ 0 }; i < listNames.size(); ++i)
    {
        cout << i + 1 << ". " << listNames.at(i) << '\n';
    }
    cout << '\n';

    cout << "what do you want to set as the current list?\n\n";

    cout << "> ";
    cin >> response;

    clear();

    cout << "are you sure you want to replace the current list?\n\n";

    cout << "> ";
    getline(cin >> ws, replaceResponse);

    if (replaceResponse == "yes" || replaceResponse == "y")
    {
        clear();

        if (listOfLists.at(response - 1).size() == 0)
        {
            cout << "this list does not exist\n\n";
            cout << "> ";

            sleep(2);
            setCurrentList();
        }
        else
        {
            currentList.clear();
            currentListChecked.clear();

            currentList = listOfLists[response - 1];
            currentListChecked = listOfListsChecked[response - 1];
            currentListName = listNames[response - 1];

            cout << "successfully replaced current list with " << currentListName << "\n\n";
            cout << "> ";

            sleep(2);
            returnTo("listSettings");
        }
    }
    else if (replaceResponse == "no" || replaceResponse == "n")
    {
        returnTo("menu");
    }
    else
    {
        invalidInput("please specify yes or no", "setCurrentList");
    }
}

void setListName(bool reset)
{
    clear();
    title("set list name");

    string name{};

    cout << "input list name: \n\n";

    cout << "> ";
    getline(cin >> ws, name);

    clear();
    
    for (int i{ 0 }; i < listNames.size(); ++i)
    {
        if (name == listNames[i])
        {
            cout << "this name already exists\n\n";
            cout << "> ";

            sleep(2);
            if (reset)
            {
                returnTo("listSettings");
            }
            else
            {
                setListName(false);
            }
        }
    }

    currentListName = name;

    if (reset)
    {
        clear();

        cout << "successfully set list name to " << name << "\n\n";
        cout << "> ";

        sleep(2);
        returnTo("listSettings");
    }

    addIndices();
}

// ------- \\

void addIndex()
{
    clear();
    title("add index");

    string index{};

    for (int i{ 0 }; i < currentList.size(); ++i)
    {
        cout << i + 1 << ". " << currentList.at(i) << '\n';
    }
    cout << '\n';

    cout << "input index to add: \n\n";

    cout << "> ";
    getline(cin >> ws, index);

    clear();

    currentList.push_back(index);
    for (int i{ 0 }; i < listNames.size(); ++i)
    {
        if (currentListName == listNames[i])
        {
            listOfLists[i].push_back(index);
        }
    }

    // cout << currentList.size() << ". " << currentList.at(currentList.size() - 1) << '\n';
    for (int i{ 0 }; i < currentList.size(); ++i)
    {
        cout << i + 1 << ". " << currentList.at(i) << '\n';
    }
    cout << '\n';

    cout << "successfully added index to current list\n\n";
    cout << "> ";

    sleep(2);
    returnTo("listSettings");
}

void removeIndex()
{
    clear();
    title("remove index");

    int index{};
    string response{};

    for (int i{ 0 }; i < currentList.size(); ++i)
    {
        cout << i + 1 << ". " << currentList.at(i) << '\n';
    }
    cout << '\n';

    cout << "input index to remove: \n\n";

    cout << "> ";
    cin >> index;

    clear();

    cout << index << ". " << currentList.at(index - 1) << '\n';
    cout << "are you sure you want to remove this index?\n\n";

    cout << "> ";
    getline(cin >> ws, response);

    if (response == "yes" || response == "y")
    {
        clear();

        cout << index << ". " << currentList.at(index - 1) << '\n';

        currentList.erase(currentList.begin() + index - 1);
        for (int i{ 0 }; i < listNames.size(); ++i)
        {
            if (currentListName == listNames[i])
            {
                listOfLists[i].erase(listOfLists[i].begin() + index - 1);
            }
        }

        cout << "successfully removed index from current list\n\n";
        cout << "> ";

        sleep(2);
        returnTo("listSettings");
    }
    else if (response == "no" || response == "n")
    {
        returnTo("listSettings");
    }
    else
    {
        invalidInput("please specify yes or no", "listSettings");
    }
}

void addRemoveIndexHandler()
{
    clear();
    title("add/remove index");

    string response{};

    cout << "will you be adding or removing an index?\n\n";

    cout << "> ";
    getline(cin >> ws, response);

    if (response == "adding" || response == "add" || response == "a" || response == "1")
    {
        addIndex();
    }
    else if (response == "removing" || response == "remove" || response == "r" || response == "2")
    {
        removeIndex();
    }
    else
    {
        invalidInput("please specify add or remove", "addRemoveIndexHandler");
    }
}

// ------- \\

void createList(bool alreadyMade)
{
    clear();
    title("create list");

    if (!alreadyMade)
    {
        setListName(false);
    }
    else
    {
        clear();

        string response{};

        cout << currentListName << "\n\n";
        for (int i{ 0 }; i < currentList.size(); ++i)
        {
            cout << i + 1 << ". " << currentList.at(i) << '\n';
        }
        cout << '\n';

        cout << "are you satisfied with this list?\n\n";

        cout << "> ";
        getline(cin >> ws, response);

        if (response == "yes" || response == "y")
        {
            listOfLists.push_back(currentList);
            listOfListsChecked.push_back(currentListChecked);
            listNames.push_back(currentListName);

            clear();

            cout << "successfully created list\n\n";
            cout << "> ";

            sleep(2);
            returnTo("menu");
        }
        else if (response == "no" || response == "n")
        {
            currentList.clear();
            currentListChecked.clear();
            currentListName.clear();

            returnTo("menu");
        }
        else
        {
            invalidInput("please specify yes or no", "createList");
        }
    }
}

// ------- \\

void saveCurrentList()
{
    clear();
    title("save current list");

    string response{};

    cout << "are you sure you want to save your current list?\n";
    cout << "note: this will overwrite your current save file\n\n";

    cout << "> ";
    getline(cin >> ws, response);

    if (response == "yes" || response == "y")
    {
        clear();

        output.open("save.txt");

        output << '$' << currentListName << '\n';

        for (int i{ 0 }; i < currentList.size(); ++i)
        {
            output << '!' << currentList.at(i) << '\n';
            output << '#' << currentListChecked.at(i) << "\n\n";
        }

        output.close();

        cout << "successfully saved list to save file\n\n";
        cout << "> ";

        sleep(2);
        returnTo("saveLoadMenu");
    }
    else if (response == "no" || response == "n")
    {
        returnTo("saveLoadMenu");
    }
    else
    {
        invalidInput("please specify yes or no", "saveCurrentList");
    }
}

void loadSavedList()
{
    clear();
    title("load saved list");

    string response{};

    cout << "are you sure you want to load your saved list?\n";
    cout << "note: this will unload your currently loaded saved list\n\n";

    cout << "> ";
    getline(cin >> ws, response);

    if (response == "yes" || response == "y")
    {
        clear();

        string line{};

        currentListName.clear();
        currentList.clear();
        currentListChecked.clear();

        // i'm surprised i got this working first try
        input.open("save.txt");

        while (getline(input, line))
        {
            if (line[0] == '$')
            {
                currentListName = line.substr(1, line.length());
            }
            else if (line[0] == '!')
            {
                currentList.push_back(line.substr(1, line.length()));
            }
            else if (line[0] == '#')
            {
                currentListChecked.push_back(stoi(line.substr(1, line.length())));
            }
        }

        input.close();

        listNames.push_back(currentListName);
        listOfLists.push_back(currentList);
        listOfListsChecked.push_back(currentListChecked);

        cout << "successfully loaded list from save file\n\n";
        cout << "> ";

        sleep(2);
        returnTo("saveLoadMenu");
    }
    else if (response == "no" || response == "n")
    {
        returnTo("saveLoadMenu");
    }
    else
    {
        invalidInput("please specify yes or no", "saveCurrentList");
    }
}

void help()
{
    clear();
    title("save/load help");

    cout << "to save your current list, select the save current list option\n";
    cout << "once your current list is saved, a file named \"save.txt\" will be created\n";
    cout << "the file is located in the directory that the executable is present\n";
    cout << "remember: this will overwrite any save files that are already in the directory\n\n";

    cout << "to load your saved list, select the load current list option\n";
    cout << "once your saved list is loaded, it will be set as the current list\n";
    cout << "if you load another list, that list will be removed from the current list\n";
    
    cout << "to make your own load file, first specify the title\n";
    cout << "to tell the program that the line is the title, place a dollar sign ($) in front of it\n";
    cout << "remember: the title only needs to be specified once\n";
    cout << "then, input an index and place an exclamation point (!) in front of it\n";
    cout << "finally, input a 0 or 1: 0 indicating that the index is unchecked, and 1 indicating that it is checked\n";
    cout << "place a hashtag (#) in front of the check\n\n";

    cout << "example: \n";
    cout << "$very cool list title\n\n";

    cout << "!awesome index\n";
    cout << "#0\n\n";

    cout << "!atonishing index\n";
    cout << "#1\n\n";

    cout << "!outstanding index\n";
    cout << "#0\n\n";

    cout << "if still confused, use your brain\n";
    cout << "if you don't have a brain currently present in your cranium,\n";
    cout << "please seek medical attention immediatelly and/or contact me for help\n";
    cout << "(my contacts can be found at https://chapel1337.github.io/contacts) \n\n";

    pause();
    returnTo("saveLoadMenu");
}

void saveLoadMenu()
{
    clear();
    title("save/load menu");

    char response{};

    cout << "save/load menu\n\n";

    cout << "1. save current list\n";
    cout << "2. load saved list\n";
    cout << "3. help\n";
    cout << "4. back\n\n";

    response = ccin();

    switch (response)
    {
    case '1':
        saveCurrentList();
        break;

    case '2':
        loadSavedList();
        break;

    case '3':
        help();
        break;

    case '4':
        returnTo("menu");
        break;

    default:
        invalidInput("please specify 1, 2, 3, or 4", "saveLoadMenu");
        break;
    }
}

// ------- \\

void checkIndex()
{
    clear();
    title("check index");

    int index{};

    for (int i{ 0 }; i < currentList.size(); ++i)
    {
        if (currentListChecked[i] == 1)
        {
            cout << i + 1 << ". " << currentList.at(i) << " [DONE]\n";
        }
        else
        {
            cout << i + 1 << ". " << currentList.at(i) << '\n';
        }
    }
    cout << '\n';

    cout << "input index to check: \n\n";

    cout << "> ";
    cin >> index;

    clear();

    currentListChecked.at(index - 1) = 1;
    for (int i{ 0 }; i < listNames.size(); ++i)
    {
        if (currentListName == listNames[i])
        {
            listOfListsChecked[i][index - 1] = 1;
        }
    }

    for (int i{ 0 }; i < currentList.size(); ++i)
    {
        if (currentListChecked[i] == 1)
        {
            cout << i + 1 << ". " << currentList.at(i) << " [DONE]\n";
        }
        else
        {
            cout << i + 1 << ". " << currentList.at(i) << '\n';
        }
    }
    cout << '\n';

    cout << "successfully checked index " << currentList.at(index - 1) << "\n\n";
    cout << "> ";

    sleep(2);
    returnTo("listSettings");
}

void uncheckIndex()
{
    clear();
    title("uncheck index");

    int index{};

    for (int i{ 0 }; i < currentList.size(); ++i)
    {
        if (currentListChecked[i] == 1)
        {
            cout << i + 1 << ". " << currentList.at(i) << " [DONE]\n";
        }
        else
        {
            cout << i + 1 << ". " << currentList.at(i) << '\n';
        }
    }
    cout << '\n';

    cout << "input index to uncheck: \n\n";

    cout << "> ";
    cin >> index;

    clear();

    currentListChecked.at(index - 1) = 0;
    for (int i{ 0 }; i < listNames.size(); ++i)
    {
        if (currentListName == listNames[i])
        {
            listOfListsChecked[i][index - 1] = 0;
        }
    }

    for (int i{ 0 }; i < currentList.size(); ++i)
    {
        if (currentListChecked[i] == 1)
        {
            cout << i + 1 << ". " << currentList.at(i) << " [DONE]\n";
        }
        else
        {
            cout << i + 1 << ". " << currentList.at(i) << '\n';
        }
    }
    cout << '\n';

    cout << "successfully unchecked index " << currentList.at(index - 1) << "\n\n";
    cout << "> ";

    sleep(2);
    returnTo("listSettings");
}

void checkUncheckIndexHandler()
{
    clear();
    title("check/uncheck index");

    string response{};

    cout << "will you be checking or unchecking an index?\n\n";

    cout << "> ";
    getline(cin >> ws, response);

    if (response == "check" || response == "c" || response == "1")
    {
        checkIndex();
    }
    else if (response == "uncheck" || response == "u" || response == "2")
    {
        uncheckIndex();
    }
    else
    {
        invalidInput("please specify check or uncheck", "checkUncheckIndexHandler");
    }
}

// ------- \\

void listSettings()
{
    clear();
    title("list settings");

    if (currentList.size() == 0)
    {
        cout << "there are no lists!\n\n";
        cout << "> ";
        
        sleep(2);
        returnTo("menu");
    }
    else
    {
        char response{};

        cout << "list settings\n\n";

        cout << "1. list all lists\n";
        cout << "2. set current list\n";
        cout << "3. set list name\n";
        cout << "4. add/remove index\n";
        cout << "5. check/uncheck index\n";
        cout << "6. back\n\n";

        cout << "> ";
        response = ccin();

        switch (response)
        {
        case '1':
            displayLists();
            break;

        case '2':
            setCurrentList();
            break;

        case '3':
            setListName(false);
            break;

        case '4':
            addRemoveIndexHandler();
            break;

        case '5':
            checkUncheckIndexHandler();
            break;

        case '6':
            returnTo("menu");
            break;

        default:
            invalidInput("please specify 1, 2, 3, 4, 5, or 6", "listSettings");
            break;
        }
    }
}

void quit()
{
    clear();

    for (int i{ 3 }; i > 0; --i)
    {
        title("exiting in ", i);

        cout << "okay, exiting in " << i;

        sleep(1);
        clear();
    }

    exit(1);
}

// ------- \\

void menu()
{
    clear();
    title("menu");

    char response{};

    cout << "list creator\n\n";

    cout << "1. create list\n";
    cout << "2. list settings\n";
    cout << "3. save/load menu\n";
    cout << "4. quit\n\n";

    cout << "> ";
    response = ccin();

    switch (response)
    {
    case '1':
        createList(false);
        break;

    case '2':
        listSettings();
        break;

    case '3':
        saveLoadMenu();
        break;

    case '4':
        quit();
        break;

    default:
        invalidInput("please specify 1, 2, 3, or 4", "menu");
        break;
    }
}

// ------- \\

void returnTo(string returnFunction)
{
    if (returnFunction == "menu")
    {
        menu();
    }
    else if (returnFunction == "listSettings")
    {
        listSettings();
    }
    else if (returnFunction == "saveLoadMenu")
    {
        saveLoadMenu();
    }

    else if (returnFunction == "setCurrentList")
    {
        setCurrentList();
    }
    else if (returnFunction == "createList")
    {
        createList(true);
    }

    else if (returnFunction == "addRemoveIndexHandler")
    {
        addRemoveIndexHandler();
    }
    else if (returnFunction == "checkUncheckIndexHandler")
    {
        checkUncheckIndexHandler();
    }

    else if (returnFunction == "saveCurrentList")
    {
        saveCurrentList();
    }
    else if (returnFunction == "loadCurrentList")
    {
        loadSavedList();
    }
}

int main()
{
    cout << "written by chapel1337\n";
    cout << "started on 10/26/2022, finished on 10/28/2022\n";

    sleep(2);

    beep();
    menu();
}

// ------- \\