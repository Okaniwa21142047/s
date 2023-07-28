#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <fstream>
using namespace std;

class RecommendedFood {
public:
    string name;
    double protein;
    double fat;
    double carbohydrate;

    RecommendedFood(string name, double protein, double fat, double carbohydrate)
        : name(name), protein(protein), fat(fat), carbohydrate(carbohydrate) {}
};

class RecommendedDinner {
public:
    string name;

    RecommendedDinner(string name)
        : name(name) {}
};

void getInput(double& weight, double& height, int& age, double& activityLevel, char& gender, char& goalChoice) {

    cout << "体重（kg）を入力してください。: ";
    cin >> weight;
    while (cin.fail()) {
        cout << "正しい体重を入力してください。: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> weight;
    }

    cout << "身長（cm）を入力してください。: ";
    cin >> height;
    while (cin.fail()) {
        cout << "正しい身長を入力してください。: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> height;
    }

    cout << "年齢を入力してください。: ";
    cin >> age;
    while (cin.fail()) {
        cout << "正しい年齢を入力してください。: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> age;
    }

    cout << "活動の様子を1、1.75、2のいずれかで入力してください。\n 1・・・生活の大部分が座位で、静的な活動が中心 \n 1.75・・・座位中心の仕事だが、職場内での移動や、通勤・買物・家事、軽いスポーツ等を行う \n 2・・・移動や立位の多い仕事や、スポーツなど余暇における活発な運動習慣をもっている: ";
    cin >> activityLevel;
    while (activityLevel != 1.0 && activityLevel != 1.75 && activityLevel != 2.0) {
        cout << "正しい活動の様子を入力してください。: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> activityLevel;
    }

    cout << "性別を入力してください。(男性: M, 女性: F): ";
    cin >> gender;
    while (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f') {
        cout << "正しい性別を入力してください。(男性: M, 女性: F): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> gender;
    }

    cout << "目標を選択してください。(減量: D, 増量: I): ";
    cin >> goalChoice;
    while (goalChoice != 'D' && goalChoice != 'd' && goalChoice != 'I' && goalChoice != 'i') {
        cout << "正しい目標を入力してください。(減量: D, 増量: I): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> goalChoice;
    }
}

void saveRecommendedDinnersToFile(const vector<RecommendedDinner>& dinners, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const RecommendedDinner& dinner : dinners) {
            file << dinner.name << endl;
        }
        file.close();
    }
}

vector<RecommendedDinner> readRecommendedDinnersFromFile(const string& filename) {
    vector<RecommendedDinner> dinners;
    ifstream file(filename);
    if (file.is_open()) {
        string dinnerName;
        while (getline(file, dinnerName)) {
            dinners.push_back(RecommendedDinner(dinnerName));
        }
        file.close();
    }
    return dinners;
}

int main() {
    srand(time(0));

    double weight, height;
    int age;
    double activityLevel;
    char gender;
    char goalChoice;

    getInput(weight, height, age, activityLevel, gender, goalChoice);

    double bmr;
    if (gender == 'M' || gender == 'm') {
        bmr = (0.0481 * weight + 0.0234 * height - 0.0138 * age - 0.4235) * 1000 / 4.186;
    }
    else if (gender == 'F' || gender == 'f') {
        bmr = (0.0481 * weight + 0.0234 * height - 0.0138 * age - 0.9708) * 1000 / 4.186;
    }
    else {
        
        return 0;
    }

    double calorie = bmr * activityLevel;

    cout << "基礎代謝: " << bmr << " kcal" << endl;
    cout << "消費カロリー: " << calorie << " kcal" << endl;

    double targetCalorie;
    if (goalChoice == 'D' || goalChoice == 'd') {
        targetCalorie = calorie - 500;
    }
    else if (goalChoice == 'I' || goalChoice == 'i') {
        targetCalorie = calorie + 500;
    }
    else {
   
        return 0;
    }

    cout << "目標摂取カロリー: " << targetCalorie << " kcal" << endl;

    double protein = weight * 2.5;
    double fat = targetCalorie * 0.2 / 9;
    double carbohydrate = (targetCalorie * 0.8 - weight * 10) / 4;

    cout << "適切なタンパク質(P)の量: " << protein << " g程度" << endl;
    cout << "適切な脂質(F)の量: " << fat << " g程度" << endl;
    cout << "適切な炭水化物(C)の量: " << carbohydrate << " g程度" << endl;

    vector<RecommendedFood> recommendedFoods = {
        RecommendedFood("・鶏むね肉100g", 22.3, 1.5, 0),
        RecommendedFood("・鶏モモ肉100g", 18.8, 3.9, 0),
        RecommendedFood("・牛赤身肉100g", 22.5, 4.6, 0.5),
        RecommendedFood("・マグロ赤身の刺身100g", 26.4, 1.4, 0.1),
        RecommendedFood("・卵1個", 6.4, 5.4, 0.2),
        RecommendedFood("・納豆1パック", 8.4, 4.9, 7.4),
        RecommendedFood("・ツナ缶ノンオイル", 11.6, 0.2, 0.1),
    };

    cout << "< おすすめの食材 > " << endl;
    for (const RecommendedFood& food : recommendedFoods) {
        cout << food.name << " P " << food.protein << "g   F " << food.fat << "g   C " << food.carbohydrate << "g" << endl;
    }

    vector<RecommendedDinner> recommendedDinners = {
        RecommendedDinner("・鶏むね豆腐ハンバーグ"),
        RecommendedDinner("・鶏むね親子丼"),
        RecommendedDinner("・鶏むねひき肉麻婆豆腐"),
        RecommendedDinner("・鶏ももトマト煮"),
        RecommendedDinner("・鶏むねひき肉ドライカレー"),
        RecommendedDinner("・鶏むねそぼろ"),
        RecommendedDinner("・牛赤身ステーキ"),
        RecommendedDinner("・お刺身"),
        RecommendedDinner("・鶏ささみのしゃぶしゃぶ"),
        RecommendedDinner("・揚げない鶏むねヤンニョムチキン"),
    };

    const string recommendedDinnersFile = "recommended_dinners.txt";

    saveRecommendedDinnersToFile(recommendedDinners, recommendedDinnersFile);

    vector<RecommendedDinner> recommendedDinnersFromFile = readRecommendedDinnersFromFile(recommendedDinnersFile);

    cout << "< 今週のおすすめ低脂質晩御飯7選 > " << endl;

    srand(time(0));
    std::shuffle(recommendedDinnersFromFile.begin(), recommendedDinnersFromFile.end(), std::mt19937(std::random_device()()));

    vector<RecommendedDinner>::iterator it = recommendedDinnersFromFile.begin();
    for (int i = 1; it != recommendedDinnersFromFile.end() && i <= 7; ++it, ++i) {
        cout << it->name << endl;
    }

    return 0;
}