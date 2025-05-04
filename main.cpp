#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;
// Constants for the game
const int TUBE_CAPACITY = 3;     // Maximum colors per tube
const int NUM_TUBES = 7;         // Number of tubes
const float TUBE_WIDTH = 80.f;   // Width of tubes & colors
const float TUBE_HEIGHT = 200.f; // Height of tubes
const float Color_HEIGHT = 60.f; // Height of colors 
int fscore = 0;  //For scoring
float windowW = 1000.f;  //Window Width
float windowH = 700.f;   //Window Height
//Sheeraz End
// Level 1 Colors
const string level1[2][3] = {     
    {"Red", "Red", "Green"},
    {"Green", "Green", "Red"}
};
// Level 2 Colors
const string level2[3][3] = {
    {"Red", "Red", "Green"},
    {"Green", "Red", "Blue"},
    {"Blue", "Blue", "Green"}
};
// Level 3 Colors
const string level3[4][3] = {
    {"Red", "Green", "Green"},
    {"Blue", "Yellow", "Yellow"},
    {"Green", "Blue", "Red"},
    {"Yellow", "Red", "Blue"}
};
//Sheeraz Code
// Level 4 Colors
const string level4[5][3] = {
    {"Red", "Green", "Blue"},
    {"Magenta", "Green", "Blue"},
    {"Red", "Yellow", "Blue"},
    {"Green", "Yellow", "Magenta"},
    {"Yellow", "Magenta", "Red"}
};
// Level 5 Colors
const string level5[6][3] = {
    {"Red", "Green", "Yellow"},
    {"Magenta", "Red", "Cyan"},
    {"Yellow", "Magenta", "Red"},
    {"Magenta", "Yellow", "Blue"},
    {"Green", "Blue", "Cyan"},
    {"Cyan", "Blue", "Green"}
};
//Sheeraz Code End*****

// Stack to represent each tube 
class Stack {
private:
    string elements[TUBE_CAPACITY];  // Array to store colors in the stack
    int top;                         // Index of the top element 
public:
    // Constructor initializes the stack as empty
    Stack() {
        top = -1;
    }
    // Push an element into the stack
    bool push(const string color) {
        if (top < TUBE_CAPACITY - 1) {
            elements[++top] = color;
            return true;
        }
        return false; // Stack overflow
    }
    // Pop an element from the stack
    bool pop() {
        if (top >= 0) {
            --top;
            return true;
        }
        return false; // Stack underflow
    }
    // Peek the top element of the stack
    string peek() const {
        if (top >= 0) {
            return elements[top];
        }
        return ""; // Empty stack
    }
    // Check if the stack is empty
    bool isEmpty() const {
        return top == -1;
    }
    // Check the number of elements in the stack
    int size() const {
        return top + 1;
    }
    // Access elements for drawing tubes
    string getColor(int c) const {
        if (c >= 0 && c < size()) {
            return elements[c];
        }
        return "Transparent";
    }
};
//Calculating the score
void fullScore(int i, int s) {
    if (i == -1) {
        fscore--;
    }
    else if (i != s) {
        fscore++;
    }
    else if (i == s) {
        fscore;
    }
    cout << "Score: " << fscore << endl;
}
// Check if the game is won
bool isGameWon(const Stack tubes[], int a) {
    for (int i = 0; i < a; ++i) {
        if (!tubes[i].isEmpty() && tubes[i].size() != TUBE_CAPACITY) {
            return false;
        }
        string color = tubes[i].peek();
        Stack temp = tubes[i]; // Create a temporary copy of the stack
        while (!temp.isEmpty()) {
            if (temp.peek() != color)
                return false;
            temp.pop();
        }
    }
    return true;
}
// Pour color from one tube to another
bool pour(Stack& from, Stack& to) {
    if (!from.isEmpty() && (to.size() < TUBE_CAPACITY) && (to.isEmpty() || from.peek() == to.peek())) {
        to.push(from.peek());
        from.pop();
        return true;
    }
    return false; // Invalid move
}
//Convert color names to SFML colors
Color getColorName(const String& colorName) {
    if (colorName == "Red")
        return Color::Red;
    if (colorName == "Green")
        return Color::Green;
    if (colorName == "Blue")
        return Color::Blue;
    if (colorName == "Yellow")
        return Color::Yellow;
    if (colorName == "Cyan")
        return Color::Cyan;
    if (colorName == "Magenta")
        return Color::Magenta;
    else
        return Color::Transparent;
}
// Display tubes graphically
void drawTubes(RenderWindow& window, const Stack tubes[], int a) {
    for (int i = 0;i <= a;i++) {
        RectangleShape tube(Vector2f(TUBE_WIDTH, TUBE_HEIGHT));
        tube.setFillColor(Color::Transparent);
        tube.setOutlineColor(Color::Black);
        tube.setOutlineThickness(5.f);
        tube.setPosition(80.f + i * 120.f, 140.f);
        window.draw(tube);
        for (int j = 0;j <= a;j++) {
            RectangleShape water(Vector2f(TUBE_WIDTH, Color_HEIGHT));
            water.setFillColor(getColorName(tubes[i].getColor(j)));
            water.setPosition(80.f + i * 120.f, 140.f + TUBE_HEIGHT - ((j + 1) * Color_HEIGHT));
            window.draw(water);
        }
    }
}
// Draw the level windows and Play the levels (1 to 5)
void playLevel(Font& font, const string levelColors[][3], int a) {
    int activeTubes = a;  // Number of active tubes
    Stack tubes[NUM_TUBES];
    // Load tubes with colors from the array
    for (int i = 0; i < activeTubes; ++i) {
        for (int j = 0; j < 3; ++j) { // Fixed to match 3 columns per tube
            tubes[i].push(levelColors[i][j]);
        }
    }
    // Setup SFML Window and Levels Window 
    RenderWindow window(VideoMode(windowW, windowH), "Welcome to Waterscapes - Color Sort Game!");
    Text levelLabel("Level " + to_string(--a) + ":", font, 35);
    levelLabel.setFillColor(Color::Magenta);
    levelLabel.setStyle(Text::Bold | Text::Underlined | Text::Italic);
    levelLabel.setPosition(Vector2f(30.f, 40.f));
    // Restart Button 
    Text title("Restart", font, 24);
    title.setFillColor(Color::Black);
    title.setStyle(Text::Bold);
    title.setOutlineThickness(5.f);
    title.setOutlineColor(Color::White);
    title.setPosition(Vector2f(257.f, 55.f));
    RectangleShape box(Vector2f(100.f, 40.f));
    box.setFillColor(Color::Cyan);
    box.setOutlineThickness(2.f);
    box.setOutlineColor(Color::Black);
    box.setPosition(Vector2f(250.f, 50.f));
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::Black);
    scoreText.setStyle(Text::Bold);
    scoreText.setPosition(Vector2f(50.f, 370.f));
    Text border("Congratulations! You Have Won The Game", font, 24);
    border.setFillColor(Color::Blue);
    border.setStyle(Text::Bold | Text::Underlined);
    border.setPosition(Vector2f(50.f, 420.f));
    //Next Button
    Text title1("Next -->", font, 24);
    title1.setFillColor(Color::Black);
    title1.setStyle(Text::Bold);
    title1.setOutlineThickness(5.f);
    title1.setOutlineColor(Color::White);
    title1.setPosition(Vector2f(505.f, 465.f));
    RectangleShape box1(Vector2f(110.f, 40.f));
    box1.setFillColor(Color::Cyan);
    box1.setOutlineThickness(2.f);
    box1.setOutlineColor(Color::Black);
    box1.setPosition(Vector2f(500.f, 460.f));
    //Back Button
    Text title2("<-- Back", font, 24);
    title2.setFillColor(Color::Black);
    title2.setStyle(Text::Bold);
    title2.setOutlineThickness(5.f);
    title2.setOutlineColor(Color::White);
    title2.setPosition(Vector2f(105.f, 465.f));
    RectangleShape box2(Vector2f(110.f, 40.f));
    box2.setFillColor(Color::Cyan);
    box2.setOutlineThickness(2.f);
    box2.setOutlineColor(Color::Black);
    box2.setPosition(Vector2f(100.f, 460.f));
    // Sound For Clicking 
    SoundBuffer s;
    s.loadFromFile("mixkit-classic-click-1117.wav");
    Sound mySound;
    mySound.setBuffer(s);
    // Main game loop
    int selectedTube = -1;  // Track user selection initializes with no tube select
    // Music For Levels Window 
    Music m;
    m.openFromFile("mixkit-tick-tock-clock-timer-1045.wav");
    m.play();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close();
            // Handle resizing
            if (event.type == Event::Resized) {
                // Create a logical view (fixed coordinate system)
                View view(FloatRect(0, 0, 600, 500));  // Logical coordinate system: width=600, height=500
                window.setView(view);
                // Adjust the view to match the new window size
                float aspectRatio = static_cast<float>(event.size.width) / event.size.height;
                view.setSize(600 * aspectRatio, 500);  // Adjust view size proportionally
                window.setView(view);
            }
            // Handle Restart Button 
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Map the mouse position to the logical view
                Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
                if (box.getGlobalBounds().contains(mousePosition)) {
                    // Close the current window
                    window.close();
                    // Reset the game state 
                    if (levelColors == level1) {
                        fscore = 0;   // Set score of previous levels
                        playLevel(font, level1, ++a);
                    }
                    else if (levelColors == level2) {
                        fscore = 3;   // Set score of previous levels
                        playLevel(font, level2, ++a);
                    }
                    else if (levelColors == level3){
                        fscore = 8;   // Set score of previous levels
                        playLevel(font, level3, ++a);
                    }
                    else if (levelColors == level4) {
                        fscore = 18;   // Set score of previous levels
                        playLevel(font, level4, ++a);
                    }
                    else if (levelColors == level5) {
                        fscore = 30;   // Set score of previous levels
                        playLevel(font, level5, ++a);
                    }
                }
            }
            // Handle Next Button
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Map the mouse position to the logical view
                Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
                if (box1.getGlobalBounds().contains(mousePosition)) {
                    // Close the current window
                    window.close();
                    // Reset the game state 
                    if (levelColors == level1) {
                        a = a + 1;
                        playLevel(font, level2, ++a);
                    }
                    else if (levelColors == level2) {
                        a = a + 1;
                        playLevel(font, level3, ++a);
                    }
                    else if (levelColors == level3) {
                        a = a + 1;
                        playLevel(font, level4, ++a);
                    }
                    else if (levelColors == level4) {
                        a = a + 1;
                        playLevel(font, level5, ++a);
                    }
                    else if (levelColors == level5) {
                        window.close();
                    }
                }
            }
            // Handle Back Button 
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Map the mouse position to the logical view
                Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
                if (box2.getGlobalBounds().contains(mousePosition)) {
                    // Close the current window
                    window.close();
                    // Reset the game state 
                    if (levelColors == level1) {
                        window.close();
                    }
                    else if (levelColors == level2) {
                        fscore = 0;
                        playLevel(font, level1, a);
                    }
                    else if (levelColors == level3) {
                        fscore = 3;
                        playLevel(font, level2, a);
                    }
                    else if (levelColors == level4) {
                        fscore = 8;
                        playLevel(font, level3, a);
                    }
                    else if (levelColors == level5) {
                        fscore = 18;
                        playLevel(font, level4, a);
                    }
                }
            }
            // Main game loop
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Map the mouse position to the logical view
                Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
                mySound.play();
                // Check if a tube is clicked
                for (int i = 0;i <= activeTubes;i++) {
                    FloatRect boundary(80.f + i * 120.f, 140.f, TUBE_WIDTH, TUBE_HEIGHT);
                    if (boundary.contains(mousePosition)) {
                        if (selectedTube == -1) {
                            //Tube is selected from pouring
                            selectedTube = i;
                        }
                        else {
                            // Tube selected to pouring
                            if (pour(tubes[selectedTube], tubes[i])) {
                                cout << "Poured from tube " << selectedTube + 1 << " to tube " << i + 1 << endl;
                                fullScore(i + 1, selectedTube + 1);
                            }
                            else {
                                cout << "Invalid Pour Attempt\n";
                                fullScore(-1, selectedTube + 1);
                            }
                            selectedTube = -1;  // Reset selection
                        }
                    }
                }
            }
        }
        scoreText.setString("Score: " + to_string(fscore));
        window.clear(Color::White);
        window.draw(levelLabel);
        window.draw(box);
        window.draw(title);
        window.draw(box2);
        window.draw(title2);
        if (isGameWon(tubes, activeTubes)) {
            window.draw(scoreText);
            window.draw(border);
            window.draw(box1);
            window.draw(title1);
        }
        drawTubes(window, tubes, activeTubes);
        window.display();
    }
}
// Function For Setup SFML window 2
void window2(Font& font) {
    // Setup SFML window 2
    RenderWindow window2(VideoMode(windowW, windowH), "Welcome to Waterscapes - Color Sort Game!");
    window2.setFramerateLimit(60);  //not depend on SF Clock
    Text title("LEVELS", font, 24);
    title.setFillColor(Color::Magenta);
    title.setStyle(Text::Bold);
    title.setOutlineThickness(5.f);
    title.setOutlineColor(Color::Black);
    title.setPosition(Vector2f(250.f, 50.f));
    RectangleShape box1(Vector2f(100.f, 40.f));
    box1.setFillColor(Color::Blue);
    box1.setOutlineThickness(2.f);
    box1.setOutlineColor(Color::Black);
    box1.setPosition(Vector2f(50.f, 100.f));
    Text l1("Level 1", font, 24);
    l1.setFillColor(Color::White);
    l1.setStyle(Text::Bold);
    l1.setOutlineThickness(5.f);
    l1.setOutlineColor(Color::Black);
    l1.setPosition(Vector2f(58.f, 105.f));
    RectangleShape box2(Vector2f(100.f, 40.f));
    box2.setFillColor(Color::Blue);
    box2.setOutlineThickness(2.f);
    box2.setOutlineColor(Color::Black);
    box2.setPosition(Vector2f(50.f, 200.f));
    Text l2("Level 2", font, 24);
    l2.setFillColor(Color::White);
    l2.setStyle(Text::Bold);
    l2.setOutlineThickness(5.f);
    l2.setOutlineColor(Color::Black);
    l2.setPosition(Vector2f(58.f, 205.f));
    RectangleShape box3(Vector2f(100.f, 40.f));
    box3.setFillColor(Color::Blue);
    box3.setOutlineThickness(2.f);
    box3.setOutlineColor(Color::Black);
    box3.setPosition(Vector2f(50.f, 300.f));
    Text l3("Level 3", font, 24);
    l3.setFillColor(Color::White);
    l3.setStyle(Text::Bold);
    l3.setOutlineThickness(5.f);
    l3.setOutlineColor(Color::Black);
    l3.setPosition(Vector2f(58.f, 305.f));
    //sheeraz Code
    RectangleShape box4(Vector2f(100.f, 40.f));
    box4.setFillColor(Color::Blue);
    box4.setOutlineThickness(2.f);
    box4.setOutlineColor(Color::Black);
    box4.setPosition(Vector2f(50.f, 400.f));
    Text l4("Level 4", font, 24);
    l4.setFillColor(Color::White);
    l4.setStyle(Text::Bold);
    l4.setOutlineThickness(5.f);
    l4.setOutlineColor(Color::Black);
    l4.setPosition(Vector2f(58.f, 405.f));

    RectangleShape box5(Vector2f(100.f, 40.f));
    box5.setFillColor(Color::Blue);
    box5.setOutlineThickness(2.f);
    box5.setOutlineColor(Color::Black);
    box5.setPosition(Vector2f(200.f, 100.f));
    Text l5("Level 5", font, 24);
    l5.setFillColor(Color::White);
    l5.setStyle(Text::Bold);
    l5.setOutlineThickness(5.f);
    l5.setOutlineColor(Color::Black);
    l5.setPosition(Vector2f(208.f, 105.f));
    while (window2.isOpen())
    {
        Event event;
        while (window2.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window2.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window2.close();
            // Handle resizing 
            if (event.type == Event::Resized) {
                // Create a logical view (fixed coordinate system)
                View view(FloatRect(0, 0, 600, 500));  // Logical coordinate system: width=600, height=500
                window2.setView(view);
                // Adjust the view to match the new window size
                float aspectRatio = static_cast<float>(event.size.width) / event.size.height;
                view.setSize(600 * aspectRatio, 500);  // Adjust view size proportionally
                window2.setView(view);
            }
            // Level 1 
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Map the mouse position to the logical view
                Vector2f mousePosition = window2.mapPixelToCoords(Mouse::getPosition(window2));
                if (box1.getGlobalBounds().contains(mousePosition)) {
                    playLevel(font, level1, 2);
                }
            }
            // Level 2 
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Map the mouse position to the logical view
                Vector2f mousePosition = window2.mapPixelToCoords(Mouse::getPosition(window2));
                if (box2.getGlobalBounds().contains(mousePosition)) {
                    playLevel(font, level2, 3);
                }
            }
            // Level 3
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Map the mouse position to the logical view
                Vector2f mousePosition = window2.mapPixelToCoords(Mouse::getPosition(window2));
                if (box3.getGlobalBounds().contains(mousePosition)) {
                    playLevel(font, level3, 4);
                }
            }
            //SHeeraz Code
            // Level 4
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Map the mouse position to the logical view
                Vector2f mousePosition = window2.mapPixelToCoords(Mouse::getPosition(window2));
                if (box4.getGlobalBounds().contains(mousePosition)) {
                    playLevel(font, level4, 5);
                }
            }
            // Level 5
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Map the mouse position to the logical view
                Vector2f mousePosition = window2.mapPixelToCoords(Mouse::getPosition(window2));
                if (box5.getGlobalBounds().contains(mousePosition)) {
                    playLevel(font, level5, 6);
                }
            }
            //sheeraz COde End
        }
        window2.clear(Color::Cyan);
        window2.draw(title);
        window2.draw(box1);
        window2.draw(l1);
        window2.draw(box2);
        window2.draw(l2);
        window2.draw(box3);
        window2.draw(l3);
        //Sheeraz Code
        window2.draw(box4);
        window2.draw(l4);
        window2.draw(box5);
        window2.draw(l5);
        window2.display();
        //Sheeraz Code End
    }
}
int main() {
    // Setup SFML window 1
    RenderWindow window1(VideoMode(windowW, windowH), "Welcome to Waterscapes - Color Sort Game!");
    window1.setFramerateLimit(60);  //not depend on SF Clock
    VertexArray square(Quads, 4);
    square[0].position = Vector2f(0.f, window1.getSize().y);
    square[1].position = Vector2f(0.f, 0.f);
    square[2].position = Vector2f(window1.getSize().x, 0.f);
    square[3].position = Vector2f(window1.getSize().x, window1.getSize().y);
    square[0].color = Color::Red;
    square[1].color = Color::Blue;
    square[2].color = Color::Green;
    square[3].color = Color::Magenta;
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Can't load ";
    }
    Text title("Welcome to Waterscapes - Color Sort Game!", font, 24);
    title.setFillColor(Color::Yellow);
    title.setStyle(Text::Bold);
    title.setOutlineThickness(5.f);
    title.setOutlineColor(Color::Black);
    title.setPosition(Vector2f(200.f, 150.f));
    RectangleShape box(Vector2f(80.f, 40.f));
    box.setFillColor(Color::Cyan);
    box.setOutlineThickness(2.f);
    box.setOutlineColor(Color::Black);
    box.setPosition(Vector2f(window1.getSize().x / 3 + 50.f, window1.getSize().y / 2));
    Text p("Play", font, 24);
    p.setFillColor(Color::White);
    p.setStyle(Text::Bold);
    p.setOutlineThickness(5.f);
    p.setOutlineColor(Color::Black);
    p.setPosition(Vector2f(window1.getSize().x / 3 + 63.f, window1.getSize().y / 2 + 4.f));
    // Music For First Window 
    Music m;
    m.openFromFile("mixkit-intro-transition-1146.wav");
    m.getLoop();
    m.play();
    while (window1.isOpen())
    {
        Event event;
        while (window1.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window1.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window1.close();
            // Handle resizing
            if (event.type == Event::Resized) {
                // Create a logical view (fixed coordinate system)
                View view(FloatRect(0, 0, 600, 500));  // Logical coordinate system: width=600, height=500
                window1.setView(view);
                // Adjust the view to match the new window size
                float aspectRatio = static_cast<float>(event.size.width) / event.size.height;
                view.setSize(600 * aspectRatio, 500);  // Adjust view size proportionally
                window1.setView(view);
            }
            // Handle Window 2 Opening 
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                // Map the mouse position to the logical view
                Vector2f mousePosition = window1.mapPixelToCoords(Mouse::getPosition(window1));
                if (box.getGlobalBounds().contains(mousePosition)) {
                    m.stop();
                    window1.close();
                    window2(font);
                }
            }
        }
        window1.clear();
        window1.draw(square);
        window1.draw(title);
        window1.draw(box);
        window1.draw(p);
        window1.display();
    }
    return 0;
}