#include <SFML/Graphics.hpp>
#include <string>

// ���̵� ���� ȭ���� �����ϴ� Ŭ����
class startLevel {
// Ŭ���� ���ο����� ����ϴ� ������ ��ȣ
private:
    sf::RenderWindow& window;    // window ��ü ����
    sf::Font font;               
    sf::Text titleText;          
    sf::Text buttonTextEasy;    
    sf::Text buttonTextNormal;   
    sf::Text buttonTextHard;    
    sf::Sprite purpleEggSprite;  
    sf::Sprite yellowEggSprite;  
    sf::Sprite greenEggSprite;   
    sf::Texture purpleEggTexture; 
    sf::Texture yellowEggTexture; 
    sf::Texture greenEggTexture;  

    // ���̵� ���� ȭ�� �ʱ�ȭ �Լ�
    void initialize() {
        // ���� �ؽ�Ʈ ����
        titleText.setFont(font);                        
        titleText.setString(sf::String(L"���̵� ����")); 
        titleText.setCharacterSize(64);                
        titleText.setFillColor(sf::Color::Black);      
        titleText.setPosition(303, 52);               

        // Easy ��ư �̹��� ����
        if (purpleEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\pupleegg.png")) {
            purpleEggSprite.setTexture(purpleEggTexture); 
            purpleEggSprite.setPosition(77, 151);      
            purpleEggSprite.setScale(190.0f / purpleEggSprite.getLocalBounds().width,
                225.0f / purpleEggSprite.getLocalBounds().height); // ũ��
        }

        // Normal ��ư �̹��� ����
        if (yellowEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\yellowegg.png")) {
            yellowEggSprite.setTexture(yellowEggTexture);
            yellowEggSprite.setPosition(314, 151);
            yellowEggSprite.setScale(190.0f / yellowEggSprite.getLocalBounds().width,
                225.0f / yellowEggSprite.getLocalBounds().height);
        }

        // Hard ��ư �̹��� ����
        if (greenEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\greenegg.png")) {
            greenEggSprite.setTexture(greenEggTexture);
            greenEggSprite.setPosition(551, 151);
            greenEggSprite.setScale(190.0f / greenEggSprite.getLocalBounds().width,
                225.0f / greenEggSprite.getLocalBounds().height);
        }

        // Easy ��ư �ؽ�Ʈ 
        buttonTextEasy.setFont(font);
        buttonTextEasy.setString("easy");              
        buttonTextEasy.setCharacterSize(64);            
        buttonTextEasy.setFillColor(sf::Color(19, 178, 231)); 
        buttonTextEasy.setPosition(120, 376);          

        // Normal ��ư �ؽ�Ʈ 
        buttonTextNormal.setFont(font);
        buttonTextNormal.setString("normal");
        buttonTextNormal.setCharacterSize(64);
        buttonTextNormal.setFillColor(sf::Color(19, 178, 231));
        buttonTextNormal.setPosition(336, 376);

        // Hard ��ư �ؽ�Ʈ 
        buttonTextHard.setFont(font);
        buttonTextHard.setString("hard");
        buttonTextHard.setCharacterSize(64);
        buttonTextHard.setFillColor(sf::Color(19, 178, 231));
        buttonTextHard.setPosition(594, 376);
    }

public:
    // ������: â�� ��Ʈ�� �޾� �ʱ�ȭ
    startLevel(sf::RenderWindow& win, const sf::Font& f)
        : window(win), font(f) {
        initialize(); // �ʱ�ȭ �Լ� ȣ��
    }

    // ���̵� ���� ȭ�� ����
    std::string run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close(); // â�� ������ ���α׷� ����
                    return "";      // �� ���ڿ� ��ȯ
                }

                // Easy ��ư Ŭ�� ����
                if (event.type == sf::Event::MouseButtonPressed &&
                    buttonTextEasy.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    // mapPixelToCoords : �־��� �ȼ� ��ǥ�� ���� ���� ��ȯ ���¸� ����� ���� ��ǥ(������ ���� �Ǵ� ���� ���������� ��ǥ)�� ��ȯ
                    return "easy";  // Easy ���̵� ���� �� "easy" ��ȯ
                }

                // Normal ��ư Ŭ�� ����
                if (event.type == sf::Event::MouseButtonPressed &&
                    buttonTextNormal.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    return "normal"; // Normal ���̵� ���� �� "normal" ��ȯ
                }

                // Hard ��ư Ŭ�� ����
                if (event.type == sf::Event::MouseButtonPressed &&
                    buttonTextHard.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    return "hard";  // Hard ���̵� ���� �� "hard" ��ȯ
                }
            }

            // ȭ���� ����� ���� �׸���
            window.clear(sf::Color(222, 231, 249)); 
            window.draw(titleText);               
            window.draw(purpleEggSprite);          
            window.draw(yellowEggSprite);         
            window.draw(greenEggSprite);           
            window.draw(buttonTextEasy);           
            window.draw(buttonTextNormal);         
            window.draw(buttonTextHard);          
            window.display();                    
        }

        return ""; // â�� �����ų� �̺�Ʈ ������ ����Ǹ� �� ���ڿ� ��ȯ
    }
};
