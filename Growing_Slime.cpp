#include <bangtal>
#include <ctime>

using namespace bangtal;

int main() {
	srand((unsigned int)time(0));

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	SoundPtr bgm = Sound::create("sounds/bgm.mp3");
	bgm->play();

	ScenePtr room = Scene::create("room", "images/기본방.png");
	ScenePtr nependeath_slime_room = Scene::create("nependeath_slime_room", "images/네펜데스슬라임.png");
	ScenePtr drunk_slime_room = Scene::create("drunk_slime_room", "images/취한슬라임.png");
	ScenePtr square_slime_room = Scene::create("square_slime_room", "images/큐브슬라임.png");
	ScenePtr king_slime_room = Scene::create("king_slime_room", "images/킹슬라임.png");
	ScenePtr angel_slime_room = Scene::create("angel_slime_room", "images/천사슬라임.png");
	ScenePtr black_slime_room = Scene::create("black_slime_room", "images/블랙슬라임.png");
	ScenePtr minigame_room = Scene::create("minigame_room", "images/미니게임방.jpg");
	ScenePtr minigame1 = Scene::create("minigame1", "images/미니게임1.jpg");
	ScenePtr minigame2 = Scene::create("minigame2", "images/미니게임2.jpg");
	ScenePtr minigame3 = Scene::create("minigame3", "images/미니게임3.jpg");
	ScenePtr shop = Scene::create("shop", "images/상점.png");
	ScenePtr study_room = Scene::create("study_room", "images/공부방.jpg");

	//상점 골드
	int money = 0;

	auto gold = Object::create("images/메소.png", shop, 150, 600, false);
	auto gold2 = Object::create("images/메소.png", shop, 220, 600, false);
	auto gold3 = Object::create("images/메소.png", shop, 290, 600, false);

	//*****기본*****
	auto melt_slime = Object::create("images/녹은슬라임.png", room, 480, 100, false);

	auto slime = Object::create("images/슬라임.png", room, 500, 150);
	slime->setScale(5.0f);
	slime->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		melt_slime->show();
		slime->hide();

		return true;
		});

	melt_slime->setScale(0.8f);
	melt_slime->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		slime->show();
		melt_slime->hide();

		return true;
		});

	auto talk = Object::create("images/기본말풍선.png", room, 700, 350);
	auto talk2 = Object::create("images/몸이이상해.png", room, 700, 350, false);
	auto talk3 = Object::create("images/ZZZ.png", room, 725, 370, false);

	auto grow_to_nependeathslime = Object::create("images/네펜데스진화.png", room, 533, 30, false);
	grow_to_nependeathslime->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		nependeath_slime_room->enter();

		return true;
		});

	auto grow_to_drunkslime = Object::create("images/취한슬라임진화.png", room, 533, 30, false);
	grow_to_drunkslime->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		drunk_slime_room->enter();

		return true;
		});

	auto grow_to_squareslime = Object::create("images/큐브슬라임진화.png", room, 533, 30, false);
	grow_to_squareslime->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		square_slime_room->enter();

		return true;
		});

	auto grow_to_kingslime = Object::create("images/킹슬라임진화.png", room, 533, 30, false);
	grow_to_kingslime->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		king_slime_room->enter();

		return true;
		});

	auto grow_to_angelslime = Object::create("images/천사슬라임진화.png", room, 533, 30, false);
	grow_to_angelslime->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		angel_slime_room->enter();

		return true;
		});

	auto grow_to_blackslime = Object::create("images/블랙슬라임진화.png", room, 533, 30, false);
	grow_to_blackslime->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		black_slime_room->enter();

		return true;
		});

	auto minigame_button = Object::create("images/미니게임버튼.png", room, 50, 0);
	minigame_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		minigame_room->enter();

		return true;
		});

	auto shop_button = Object::create("images/상점버튼.png", room, 300, 0);
	shop_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		shop->enter();

		return true;
		});

	auto study_button = Object::create("images/공부버튼.png", room, 800, 0);
	study_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		study_room->enter();

		return true;
		});

	int sleep_cnt = 0;

	TimerPtr sleep_timer = Timer::create(5.f);

	auto sleep_button = Object::create("images/잠버튼.png", room, 1050, 0);
	sleep_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		sleep_cnt++;
		room->setLight(0.3f);
		sleep_timer->start();
		showTimer(sleep_timer);
		talk->hide(); talk3->show(); minigame_button->hide(); shop_button->hide(); study_button->hide();

		return true;
		});

	sleep_timer->setOnTimerCallback([&](TimerPtr timer)->bool {

		if (sleep_cnt == 10) {
			minigame_button->hide(); shop_button->hide(); study_button->hide(); sleep_button->hide(); talk->hide(); talk2->show();
			grow_to_kingslime->show();
		}
		sleep_timer->set(5.f);
		sleep_timer->stop();
		hideTimer();
		room->setLight(1.0f);
		showMessage("잘잤다!");
		talk->show(); talk3->hide(); minigame_button->show(); shop_button->show(); study_button->show();

		return true;
		});

	//*****미니게임*****
	auto minigame_slime = Object::create("images/미니게임슬라임.png", minigame_room, 800, 170);
	minigame_slime->setScale(5.0f);

	auto minigame_talk = Object::create("images/미니게임말풍선.png", minigame_room, 970, 370);

	auto minigame_to_room = Object::create("images/뒤로가기.png", minigame_room, 1150, 20);
	minigame_to_room->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		room->enter();

		return true;
		});

	//*****미니게임1*****
	int minigame1_cnt = 0;
	int minigame1_try = 0;
	bool minigame1_unclear = true;

	TimerPtr minigame1_timer = Timer::create(20.f);
	minigame1_timer->setOnTimerCallback([&](TimerPtr timer)->bool {

		minigame1_timer->set(20.f);
		minigame1_timer->stop();
		hideTimer();
		room->enter();
		showMessage("실패!\n 처음부터 다시 도전하자.");
		minigame1_try++;

		return true;
		});

	auto minigame1_slime3 = Object::create("images/미니게임1_3단계슬라임.png", minigame1, 0 + rand() % 1201, 0 + rand() % 651, false);
	minigame1_slime3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame1_cnt < 30) {
			minigame1_slime3->locate(minigame1, 0 + rand() % 1201, 0 + rand() % 651);
			minigame1_cnt++;
		}
		else {
			minigame1_slime3->hide();
			minigame1_timer->stop();
			hideTimer();
			minigame1_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold->show();
			money++;
			room->enter();
		}

		return true;
		});

	auto minigame1_slime2 = Object::create("images/미니게임1_2단계슬라임.png", minigame1, 0 + rand() % 1201, 0 + rand() % 651, false);
	minigame1_slime2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame1_cnt < 20) {
			minigame1_slime2->locate(minigame1, 0 + rand() % 1201, 0 + rand() % 651);
			minigame1_cnt++;
		}
		else {
			minigame1_slime2->hide();
			minigame1_slime3->show();
		}

		return true;
		});

	auto minigame1_slime1 = Object::create("images/미니게임1_1단계슬라임.png", minigame1, 0 + rand() % 1201, 0 + rand() % 651);
	minigame1_slime1->setScale(2.0f);
	minigame1_slime1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame1_cnt < 10) {
			minigame1_slime1->locate(minigame1, 0 + rand() % 1201, 0 + rand() % 651);
			minigame1_cnt++;
		}
		else {
			minigame1_slime1->hide();
			minigame1_slime2->show();
		}

		return true;
		});

	auto minigame1_game_machine = Object::create("images/게임기1.png", minigame_room, 320, 120);
	minigame1_game_machine->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame1_unclear) {
			if (minigame1_try > 0) {
				minigame1_cnt = 0;
				minigame1_slime1->show();
				minigame1_slime2->hide();
				minigame1_slime3->hide();
			}
			minigame1->enter();
			showMessage("변형된 슬라임들을 처치하자!");
			minigame1_timer->start();
			showTimer(minigame1_timer);
		}

		return true;
		});

	//*****미니게임2*****
	int minigame2_cnt = 0;
	int minigame2_try = 0;
	bool minigame2_unclear = true;

	auto minigame2_slime = Object::create("images/미니게임2_슬라임.png", minigame2, 850, 20);
	minigame2_slime->setScale(2.5f);

	auto minigame2_Q1 = Object::create("images/1번문제.png", minigame2, 250, 50);
	auto minigame2_Q2 = Object::create("images/2번문제.png", minigame2, 250, 50, false);
	auto minigame2_Q3 = Object::create("images/3번문제.png", minigame2, 250, 50, false);
	auto minigame2_Q4 = Object::create("images/4번문제.png", minigame2, 250, 50, false);
	auto minigame2_Q5 = Object::create("images/5번문제.png", minigame2, 250, 50, false);
	auto minigame2_Q6 = Object::create("images/6번문제.png", minigame2, 250, 50, false);
	auto minigame2_Q7 = Object::create("images/7번문제.png", minigame2, 250, 50, false);

	auto minigame2_A2 = Object::create("images/주황풍선_3.png", minigame2, 260, 400);
	minigame2_A2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame2_cnt == 0) {
			minigame2_A2->hide();
			minigame2_Q1->hide();
			minigame2_Q2->show();
			minigame2_cnt++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame2_try++;
		}

		return true;
		});

	auto minigame2_A1 = Object::create("images/빨강풍선_10.png", minigame2, 100, 400);
	minigame2_A1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame2_cnt == 1) {
			minigame2_A1->hide();
			minigame2_Q2->hide();
			minigame2_Q3->show();
			minigame2_cnt++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame2_try++;
		}

		return true;
		});

	auto minigame2_A5 = Object::create("images/파랑풍선_18.png", minigame2, 740, 400);
	minigame2_A5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame2_cnt == 2) {
			minigame2_A5->hide();
			minigame2_Q3->hide();
			minigame2_Q4->show();
			minigame2_cnt++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame2_try++;
		}

		return true;
		});

	auto minigame2_A7 = Object::create("images/보라풍선_34.png", minigame2, 1060, 400);
	minigame2_A7->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame2_cnt == 3) {
			minigame2_A7->hide();
			minigame2_Q4->hide();
			minigame2_Q5->show();
			minigame2_cnt++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame2_try++;
		}

		return true;
		});

	auto minigame2_A6 = Object::create("images/남색풍선_6.png", minigame2, 900, 400);
	minigame2_A6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame2_cnt == 4) {
			minigame2_A6->hide();
			minigame2_Q5->hide();
			minigame2_Q6->show();
			minigame2_cnt++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame2_try++;
		}

		return true;
		});

	auto minigame2_A3 = Object::create("images/노랑풍선_410.png", minigame2, 420, 400);
	minigame2_A3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame2_cnt == 5) {
			minigame2_A3->hide();
			minigame2_Q6->hide();
			minigame2_Q7->show();
			minigame2_cnt++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame2_try++;
		}

		return true;
		});

	auto minigame2_A4 = Object::create("images/초록풍선_5.png", minigame2, 580, 400);
	minigame2_A4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame2_cnt == 6) {
			room->enter();
			minigame2_unclear = false;
			showMessage("껄껄껄 수고했네\n 보상으로 10골드를 주겠네.");
			gold2->show();
			money++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame2_try++;
		}

		return true;
		});

	auto minigame2_game_machine = Object::create("images/게임기2.png", minigame_room, 450, 123);
	minigame2_game_machine->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame2_unclear) {
			if (minigame2_try > 0) {
				minigame2_cnt = 0;
				minigame2_Q1->show(); minigame2_Q2->hide(); minigame2_Q3->hide(); minigame2_Q4->hide(); minigame2_Q5->hide(); minigame2_Q6->hide(); minigame2_Q7->hide();
				minigame2_A1->show(); minigame2_A2->show(); minigame2_A3->show(); minigame2_A4->show(); minigame2_A5->show(); minigame2_A6->show(); minigame2_A7->show();
			}
			showMessage("고대슬라임이 내는 문제를 맞추자!");
			minigame2->enter();
		}

		return true;
		});

	//*****미니게임3*****
	int minigame3_try = 0;
	int	minigame3_cnt = 0;
	int	minigame3_turn = 0;
	bool minigame3_unclear = true;

	auto minigame3_blueslime = Object::create("images/미니게임3_슬라임1.png", minigame3, 130, 500); // 1
	auto minigame3_blueslime2 = Object::create("images/미니게임3_슬라임1.png", minigame3, 805, 500); // 4
	auto minigame3_cokeslime = Object::create("images/미니게임3_슬라임2.png", minigame3, 355, 500); // 2
	auto minigame3_cokeslime2 = Object::create("images/미니게임3_슬라임2.png", minigame3, 580, 300); // 8
	auto minigame3_redslime = Object::create("images/미니게임3_슬라임3.png", minigame3, 580, 500); // 3
	auto minigame3_redslime2 = Object::create("images/미니게임3_슬라임3.png", minigame3, 1030, 300); // 10
	auto minigame3_silverslime = Object::create("images/미니게임3_슬라임4.png", minigame3, 1030, 500); // 5
	auto minigame3_silverslime2 = Object::create("images/미니게임3_슬라임4.png", minigame3, 130, 300); // 6
	auto minigame3_goldslime = Object::create("images/미니게임3_슬라임5.png", minigame3, 355, 300); // 7
	auto minigame3_goldslime2 = Object::create("images/미니게임3_슬라임5.png", minigame3, 805, 300); // 9

	auto question_mark1 = Object::create("images/물음표.png", minigame3, 150, 500, false);
	question_mark1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_turn == 9) {
			minigame3_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold3->show();
			money++;
			room->enter();
		}
		else if (minigame3_cnt == 0) {
			question_mark1->hide();
			minigame3_blueslime->show();
			minigame3_cnt = 1;
			minigame3_turn++;
		}
		else if (minigame3_cnt == 4) {
			question_mark1->hide();
			minigame3_blueslime->show();
			minigame3_cnt = 0;
			minigame3_turn++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame3_try++;
			minigame3_cnt = 0;
		}

		return true;
		});

	auto question_mark2 = Object::create("images/물음표.png", minigame3, 375, 500, false);
	question_mark2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_turn == 9) {
			minigame3_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold3->show();
			money++;
			room->enter();
		}
		else if (minigame3_cnt == 0) {
			question_mark2->hide();
			minigame3_cokeslime->show();
			minigame3_cnt = 2;
			minigame3_turn++;
		}
		else if (minigame3_cnt == 8) {
			question_mark2->hide();
			minigame3_cokeslime->show();
			minigame3_cnt = 0;
			minigame3_turn++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame3_try++;
			minigame3_cnt = 0;
		}

		return true;
		});

	auto question_mark3 = Object::create("images/물음표.png", minigame3, 600, 500, false);
	question_mark3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_turn == 9) {
			minigame3_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold3->show();
			money++;
			room->enter();
		}
		else if (minigame3_cnt == 0) {
			question_mark3->hide();
			minigame3_redslime->show();
			minigame3_cnt = 3;
			minigame3_turn++;
		}
		else if (minigame3_cnt == 10) {
			question_mark3->hide();
			minigame3_redslime->show();
			minigame3_cnt = 0;
			minigame3_turn++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame3_try++;
			minigame3_cnt = 0;
		}

		return true;
		});

	auto question_mark4 = Object::create("images/물음표.png", minigame3, 825, 500, false);
	question_mark4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_turn == 9) {
			minigame3_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold3->show();
			money++;
			room->enter();
		}
		else if (minigame3_cnt == 0) {
			question_mark4->hide();
			minigame3_blueslime2->show();
			minigame3_cnt = 4;
			minigame3_turn++;
		}
		else if (minigame3_cnt == 1) {
			question_mark4->hide();
			minigame3_blueslime2->show();
			minigame3_cnt = 0;
			minigame3_turn++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame3_try++;
			minigame3_cnt = 0;
		}

		return true;
		});

	auto question_mark5 = Object::create("images/물음표.png", minigame3, 1050, 500, false);
	question_mark5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_turn == 9) {
			minigame3_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold3->show();
			money++;
			room->enter();
		}
		else if (minigame3_cnt == 0) {
			question_mark5->hide();
			minigame3_silverslime->show();
			minigame3_cnt = 5;
			minigame3_turn++;
		}
		else if (minigame3_cnt == 6) {
			question_mark5->hide();
			minigame3_silverslime->show();
			minigame3_cnt = 0;
			minigame3_turn++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame3_try++;
			minigame3_cnt = 0;
		}

		return true;
		});

	auto question_mark6 = Object::create("images/물음표.png", minigame3, 150, 300, false);
	question_mark6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_turn == 9) {
			minigame3_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold3->show();
			money++;
			room->enter();
		}
		else if (minigame3_cnt == 0) {
			question_mark6->hide();
			minigame3_silverslime2->show();
			minigame3_cnt = 6;
			minigame3_turn++;
		}
		else if (minigame3_cnt == 5) {
			question_mark6->hide();
			minigame3_silverslime2->show();
			minigame3_cnt = 0;
			minigame3_turn++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame3_try++;
			minigame3_cnt = 0;
		}

		return true;
		});

	auto question_mark7 = Object::create("images/물음표.png", minigame3, 375, 300, false);
	question_mark7->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_turn == 9) {
			minigame3_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold3->show();
			money++;
			room->enter();
		}
		else if (minigame3_cnt == 0) {
			question_mark7->hide();
			minigame3_goldslime->show();
			minigame3_cnt = 7;
			minigame3_turn++;
		}
		else if (minigame3_cnt == 9) {
			question_mark7->hide();
			minigame3_goldslime->show();
			minigame3_cnt = 0;
			minigame3_turn++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame3_try++;
			minigame3_cnt = 0;
		}

		return true;
		});

	auto question_mark8 = Object::create("images/물음표.png", minigame3, 600, 300, false);
	question_mark8->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_turn == 9) {
			minigame3_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold3->show();
			money++;
			room->enter();
		}
		else if (minigame3_cnt == 0) {
			question_mark8->hide();
			minigame3_cokeslime2->show();
			minigame3_cnt = 8;
			minigame3_turn++;
		}
		else if (minigame3_cnt == 2) {
			question_mark8->hide();
			minigame3_cokeslime2->show();
			minigame3_cnt = 0;
			minigame3_turn++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame3_try++;
			minigame3_cnt = 0;
		}

		return true;
		});

	auto question_mark9 = Object::create("images/물음표.png", minigame3, 825, 300, false);
	question_mark9->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_turn == 9) {
			minigame3_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold3->show();
			money++;
			room->enter();
		}
		else if (minigame3_cnt == 0) {
			question_mark9->hide();
			minigame3_goldslime2->show();
			minigame3_cnt = 9;
			minigame3_turn++;
		}
		else if (minigame3_cnt == 7) {
			question_mark9->hide();
			minigame3_goldslime2->show();
			minigame3_cnt = 0;
			minigame3_turn++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame3_try++;
			minigame3_cnt = 0;
		}

		return true;
		});

	auto question_mark10 = Object::create("images/물음표.png", minigame3, 1050, 300, false);
	question_mark10->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_turn == 9) {
			minigame3_unclear = false;
			showMessage("성공!\n 보상으로 10골드를 얻었다.");
			gold3->show();
			money++;
			room->enter();
		}
		else if (minigame3_cnt == 0) {
			question_mark10->hide();
			minigame3_redslime2->show();
			minigame3_cnt = 10;
			minigame3_turn++;
		}
		else if (minigame3_cnt == 3) {
			question_mark10->hide();
			minigame3_redslime2->show();
			minigame3_cnt = 0;
			minigame3_turn++;
		}
		else {
			showMessage("틀렸어\n 처음부터 다시해보자");
			room->enter();
			minigame3_try++;
			minigame3_cnt = 0;
		}

		return true;
		});

	TimerPtr minigame3_timer = Timer::create(7.f);
	minigame3_timer->setOnTimerCallback([&](TimerPtr timer)->bool {

		minigame3_blueslime->hide(); minigame3_blueslime2->hide();
		minigame3_cokeslime->hide(); minigame3_cokeslime2->hide();
		minigame3_redslime->hide(); minigame3_redslime2->hide();
		minigame3_silverslime->hide(); minigame3_silverslime2->hide();
		minigame3_goldslime->hide(); minigame3_goldslime2->hide();
		question_mark1->show(); question_mark2->show(); question_mark3->show(); question_mark4->show(); question_mark5->show();
		question_mark6->show(); question_mark7->show(); question_mark8->show(); question_mark9->show(); question_mark10->show();

		minigame3_timer->set(7.f);
		minigame3_timer->stop();
		hideTimer();

		return true;
		});

	auto minigame3_game_machine = Object::create("images/게임기3.png", minigame_room, 585, 125);
	minigame3_game_machine->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (minigame3_unclear) {
			if (minigame3_try > 0) {
				question_mark1->hide(); question_mark2->hide(); question_mark3->hide(); question_mark4->hide(); question_mark5->hide();
				question_mark6->hide(); question_mark7->hide(); question_mark8->hide(); question_mark9->hide(); question_mark10->hide();
				minigame3_blueslime->show(); minigame3_blueslime2->show();
				minigame3_cokeslime->show(); minigame3_cokeslime2->show();
				minigame3_redslime->show(); minigame3_redslime2->show();
				minigame3_silverslime->show(); minigame3_silverslime2->show();
				minigame3_goldslime->show(); minigame3_goldslime2->show();
			}
			showMessage("변장한 슬라임들의 위치를 외우고\n 같은 종류끼리 묶어버리자!");
			minigame3->enter();
			minigame3_timer->start();
			showTimer(minigame3_timer);
		}

		return true;
		});

	//*****상점*****
	auto nependeath = Object::create("images/네펜데스.png", shop, 250, 262);
	nependeath->setScale(2.8f);
	nependeath->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (money == 3) {
			room->enter();
			minigame_button->hide(); shop_button->hide(); study_button->hide(); sleep_button->hide(); talk->hide(); talk2->show();
			grow_to_nependeathslime->show();
		}

		return true;
		});

	auto soju = Object::create("images/소주.png", shop, 620, 262);
	soju->setScale(0.25f);
	soju->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (money == 3) {
			room->enter();
			minigame_button->hide(); shop_button->hide(); study_button->hide(); sleep_button->hide(); talk->hide(); talk2->show();
			grow_to_drunkslime->show();
		}

		return true;
		});

	auto sqaure_drink = Object::create("images/네모물약.png", shop, 810, 215);
	sqaure_drink->setScale(0.5f);
	sqaure_drink->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (money == 3) {
			room->enter();
			minigame_button->hide(); shop_button->hide(); study_button->hide(); sleep_button->hide(); talk->hide(); talk2->show();
			grow_to_squareslime->show();
		}

		return true;
		});

	auto shop_to_room = Object::create("images/뒤로가기.png", shop, 1150, 20);
	shop_to_room->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		room->enter();

		return true;
		});

	//*****공부방*****
	auto black_study = Object::create("images/흑마법.png", study_room, 970, 100);
	black_study->setScale(3.0f);
	black_study->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (money == 3) {
			room->enter();
			minigame_button->hide(); shop_button->hide(); study_button->hide(); sleep_button->hide(); talk->hide(); talk2->show();
			grow_to_blackslime->show();
		}

		return true;
		});

	auto white_study = Object::create("images/백마법.png", study_room, 200, 100);
	white_study->setScale(3.0f);
	white_study->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (money == 3) {
			room->enter();
			minigame_button->hide(); shop_button->hide(); study_button->hide(); sleep_button->hide(); talk->hide(); talk2->show();
			grow_to_angelslime->show();
		}

		return true;
		});

	auto studyroom_to_room = Object::create("images/뒤로가기.png", study_room, 1150, 20);
	studyroom_to_room->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		room->enter();

		return true;
		});

	startGame(room);
	return 0;
}