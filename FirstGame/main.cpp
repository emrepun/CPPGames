#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int main()
{
    default_random_engine randomEngine(time(NULL));
    uniform_real_distribution<float> attack(0.0f, 1.0f);

    // Human properties
    float humanAttack = 0.6f;
    float humanHealth = 250.0f;
    float humanDamage = 200.0f;
    float currentHumanHealth = humanHealth;

    // Skeleton properties
    float skeletonAttack = 0.4f;
    float skeletonHealth = 50.0f;
    float skeletonDamage = 40.0f;
    float currentSkeletonHealth = skeletonHealth;


    float attackResult;

    int startSkeletons;
    int startHumans;

    int numbSkeletons;
    int numbHumans;

    char turn = 'H';

    cout << "*** Skeletons vs Humans! ***\n";

    // Get the numb of humans
    cout << "Enter the number of humans: ";
    cin >> numbHumans;
    startHumans = numbHumans;

    // Get the numb of skeletons
    cout << "Enter the number of skeletons: ";
    cin >> numbSkeletons;
    startSkeletons = numbSkeletons;

    cout << "\nBeginning combat!\n\n";

    while((numbHumans > 0) && (numbSkeletons > 0)) {
        // Get our attack result
        attackResult = attack(randomEngine);

        // Humans turn
        if (turn == 'H') {


            // Check if attack was successful

            if (attackResult <= humanAttack) {
                currentSkeletonHealth -= humanDamage;

                if (currentSkeletonHealth < 0) {
                    numbSkeletons--;
                    currentSkeletonHealth = skeletonHealth;
                }

            }

            turn = 'S';

        } else {
            attackResult = attack(randomEngine);

            if (attackResult <= skeletonAttack) {
                currentHumanHealth -= skeletonDamage;

                if (currentHumanHealth < 0) {
                    numbHumans--;
                    currentHumanHealth = humanHealth;
                }
            }

            turn = 'H';

        }

    }

    cout << "\nBattle is over!\n\n";

    if (numbHumans > 0) {
        cout << "Humans won!\n";
        cout << "There are "<< numbHumans << " humans left!\n";
    } else {
        cout << "Skeletons won!\n";
        cout << "There are "<< numbSkeletons << " skeletons left!\n";
    }

    cout << startHumans - numbHumans <<" humans and " << startSkeletons - numbSkeletons << " skeletons lost their lives.\n\n";


    //system("PAUSE");
    return 0;
}