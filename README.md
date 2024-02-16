# Farm Game
This game is a course project that was written in C++ programming language and QT framework. It is important to note that you should rewrite the path of the database, flags of countries, and pictures based on your local directory.

In this game, several users can register just one time, grow animals and vegetables on their farms, and make money. 

If new users want to join, you should remove all the users who already registered and then register all users.  

# Progress
1- On the main page you start the game. 

2- In the "number_of_players" page you indicate how many players will join the game.

3- In the "login" page you enter your information such as username, email, password, country code, etc.   

4- On the "scene" page, if you click on an area of the farmland, that area changes to green and prepared for farming. This has 3 coins cost. Then you could grow an animal or a vegetable. Each animal and vegetable has its special cost. To grow and feed animals and vegetables each area needs a worker. You can hire a worker through the bottom click. When you assign a worker to an animal or vegetable, the process of growing and making a product will be started. After a some while the product will be prepared and you can collect them. By collecting products, you can make money.  

# Database
I have employed the SQLite DB for this project. The user's table(game_users) is included the below items:

'''
user_Name
user_email
user_password
user_balance
user_phoneNumber
user_countryCode
user_farmId
'''


# Note: Please don't hesitate if have any questions and make an issue. 
