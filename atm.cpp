// ==================== المكتبات ====================

// إدخال وإخراج (cout / cin)
#include <iostream>

// التعامل مع الوقت (sleep)
#include <chrono>

// تشغيل delay / sleep
#include <thread>

using namespace std;

// ==================== قائمة الخيارات (Menu) ====================
// enum = تعريف قيم ثابتة بدل الأرقام العشوائية
enum enMenu {
    CheckAccount = 1,   // عرض الرصيد
    WithDraw = 2,       // سحب
    DepositCash = 3,    // إيداع
    Quit = 4            // خروج
};

// ==================== دالة إدخال آمن ====================
// الهدف: منع إدخال نص بدل رقم
int getInput(const string& prompt) {
    int value;

    while (true) {
        // عرض الرسالة للمستخدم
        cout << prompt;

        // قراءة إدخال المستخدم
        cin >> value;

        // إذا المستخدم كتب شيء غير رقم
        if (cin.fail()) {
            cin.clear();              // إعادة ضبط حالة الخطأ
            cin.ignore(10000, '\n');  // حذف الإدخال الخاطئ
            cout << "Invalid input. Please enter a number.\n";
        }
        else {
            cin.ignore(10000, '\n');  // تنظيف buffer
            return value;             // رجوع القيمة الصحيحة
        }
    }
}

// ==================== التحقق من PIN ====================
bool check_PIN() {

    int PIN = 12345;              // الرقم السري الصحيح
    int attempts = 0;             // عدد المحاولات
    const int MAX_ATTEMPTS = 3;   // أقصى عدد محاولات

    // طالما المحاولات أقل من 3
    while (attempts < MAX_ATTEMPTS) {

        // طلب PIN من المستخدم
        int input_PIN = getInput("Enter your PIN: ");

        // إذا صحيح
        if (input_PIN == PIN) {
            break; // خروج من الحلقة
        }
        else {
            attempts++; // زيادة عدد المحاولات

            cout << "Incorrect PIN. Attempts remaining: "
                 << (MAX_ATTEMPTS - attempts) << "\n";
        }

        // إذا انتهت المحاولات
        if (attempts == MAX_ATTEMPTS) {
            cout << "Too many incorrect attempts. Please wait 10 seconds...\n";

            // إيقاف البرنامج 10 ثواني
            this_thread::sleep_for(chrono::seconds(10));

            // إعادة المحاولات (لكن هذا فعليًا سلوك ضعيف منطقيًا)
            attempts = 0;
        }
    }

    // رسالة ترحيب
    cout << "\n\t\t\t================ Welcome To Service Bank ATM ================\n\t\t\t\n";

    return true;
}

// ==================== عرض القائمة ====================
void ShowMenu() {
    cout << "1.Check Account\n";
    cout << "2.Withdraw Cash\n";
    cout << "3.Deposit Cash\n";
    cout << "4.Exit\n";
}

// ==================== اختيار المستخدم ====================
enMenu ChooseMenu() {

    // أخذ رقم من المستخدم
    int choice = getInput("Choose an Option [1-4]: ");

    // تحويل الرقم إلى enum
    return static_cast<enMenu>(choice);
}

// ==================== تشغيل ATM ====================
void StartATM() {

    // التحقق من PIN قبل الدخول
    check_PIN();

    int balance = 500; // الرصيد الابتدائي

    enMenu choice;

    // حلقة البرنامج الأساسية
    do {

        ShowMenu();              // عرض القائمة
        choice = ChooseMenu();   // اختيار المستخدم

        switch (choice) {

        // ================= عرض الرصيد =================
        case enMenu::CheckAccount:
            cout << "\nYour Current Balance is: $" << balance << "\n\n";
            break;

        // ================= سحب =================
        case enMenu::WithDraw: {
            int amount = getInput("Enter amount to withdraw: ");

            // تحقق من الرصيد
            if (amount <= balance) {
                balance -= amount;
                cout << "\nYour Current Balance is: $" << balance << "\n\n";
            } else {
                cout << "\nInsufficient Funds!\n\n";
            }
            break;
        }

        // ================= إيداع =================
        case enMenu::DepositCash: {
            int amount = getInput("Enter the amount to deposit: ");

            balance += amount;

            cout << "\nYour Current Balance is: $" << balance << "\n\n";
            break;
        }

        // ================= خروج =================
        case enMenu::Quit:
            cout << "\nExiting the program...\n";
            cout << "\n\t\t\t================ Thank you for Using Service Bank ATM ================\n\n";
            break;

        // ================= خيار خاطئ =================
        default:
            cout << "\nInvalid Choice. Please try again.\n\n";
            break;
        }

    } while (choice != enMenu::Quit);
}

// ==================== main ====================
int main() {
    StartATM(); // تشغيل البرنامج
    return 0;
}