#include "ChrisJenkins.hpp"
#include <random>

lionheart::Placement lionheart::ChrisJenkins::placeUnit(UnitType,
                                                        StartBox const &box,
                                                        SituationReport report)
{
        /*Fill this out with instructions on how to place your initial units.  Without
         * changes your units will fill the starting box from top left to bottom right
         * in the order constructed.*/

        //gets the side the game is being played on.
        westSide = (box.minCol < static_cast<int>(report.things[0].size() / 2));

        //HPz.clear();

        if (westSide)
        {
                auto r = box.minRow + 8;
                auto c = box.minCol + 4;
                //set king in middle (2,4)
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                //set the 6 knights
                //1
                r = box.minRow + 4;
                c = box.minCol + 3;

                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //2
                r = box.minRow + 4;
                c = box.minCol + 4;

                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //3
                r = box.minRow + 5;
                c = box.minCol + 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //4
                r = box.minRow + 5;
                c = box.minCol + 4;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //5
                r = box.minRow + 8;
                c = box.minCol + 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //6
                r = box.minRow + 9;
                c = box.minCol + 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                //add the 8 archers
                //first the 4 gate watchers
                r = box.minRow;
                c = box.minCol + 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                r = box.minRow;
                c = box.minCol + 4;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                r = box.minRow + 1;
                c = box.minCol + 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                r = box.minRow + 2;
                c = box.minCol + 5;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                //place the remaining four archers.
                r = box.minRow + 3;
                c = box.minCol + 5;

                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };


                r = box.minRow + 6;
                c = box.minCol + 5;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                r = box.minRow + 7;
                c = box.minCol + 5;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                r = box.minRow + 9;
                c = box.minCol + 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                //place the 15 infantry
                //top ones
                //1
                r = box.minRow;
                c = box.minCol + 1;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //2
                r = box.minRow + 3;
                c = box.minCol + 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //3
                r = box.minRow + 3;
                c = box.minCol + 4;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //4
                r = box.minRow + 4;
                c = box.minCol + 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //5
                r = box.minRow + 4;
                c = box.minCol + 5;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //bottom ones
                //6
                r = box.minRow + 5;
                c = box.minCol + 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //7
                r = box.minRow + 5;
                c = box.minCol + 5;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //8
                r = box.minRow + 6;
                c = box.minCol + 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //9
                r = box.minRow + 6;
                c = box.minCol + 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //10
                r = box.minRow + 6;
                c = box.minCol + 4;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //middle ones
                //11
                r = box.minRow + 7;
                c = box.minCol + 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //12
                r = box.minRow + 7;
                c = box.minCol + 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //13
                r = box.minRow + 7;
                c = box.minCol + 4;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //14
                r = box.minRow + 8;
                c = box.minCol + 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //15
                r = box.minRow + 9;
                c = box.minCol + 1;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                /*
                   /-\/-\/-\.~~/-\/-\/-\/-\
                   /-\~,."'~~."a4>`~```"/-\
                   /-\`~'.,'~,,~``'`~'"'/-\
                   /-\,",a4>a4>,'`'"""",/-\
                   /-\'`.k2>``.k2>.".a4>/-\
                   /-\,..k2>*1>k2>..~,,'`~`
                   /-\~`.k2>`',k2>'"'''''~"
                   /-\`,'a4>a4>',~~,"a4>/-\
                   /-\.'~~`"'~,'`~'.~.',/-\
                   /-\~~~.~,"~`','~.~.",/-\
                   /-\,~",~`~`,a4>..".'~/-\
                   /-\/-\/-\'.`/-\/-\/-\/-\
                 */
        }
        else
        {
                auto r = box.minRow + 8;
                auto c = box.maxCol - 4;
                //set king in middle (2,4)
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                //set the 6 knights
                //1
                r = box.minRow + 4;
                c = box.maxCol - 3;

                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //2
                r = box.minRow + 4;
                c = box.maxCol - 4;

                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //3
                r = box.minRow + 5;
                c = box.maxCol - 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //4
                r = box.minRow + 5;
                c = box.maxCol - 4;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //5
                r = box.minRow + 8;
                c = box.maxCol - 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //6
                r = box.minRow + 9;
                c = box.maxCol - 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                //add the 8 archers
                //first the 4 gate watchers
                r = box.minRow;
                c = box.maxCol - 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                r = box.minRow;
                c = box.maxCol - 4;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                r = box.minRow + 1;
                c = box.maxCol - 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                r = box.minRow + 2;
                c = box.maxCol - 5;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                //place the remaining four archers.
                r = box.minRow + 3;
                c = box.maxCol - 5;

                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };


                r = box.minRow + 6;
                c = box.maxCol - 5;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                r = box.minRow + 7;
                c = box.maxCol - 5;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                r = box.minRow + 9;
                c = box.maxCol - 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                //place the 15 infantry
                //top ones
                //1
                r = box.minRow;
                c = box.maxCol - 1;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //2
                r = box.minRow + 3;
                c = box.maxCol - 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //3
                r = box.minRow + 3;
                c = box.maxCol - 4;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //4
                r = box.minRow + 4;
                c = box.maxCol - 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //5
                r = box.minRow + 4;
                c = box.maxCol - 5;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //bottom ones
                //6
                r = box.minRow + 5;
                c = box.maxCol - 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //7
                r = box.minRow + 5;
                c = box.maxCol - 5;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //8
                r = box.minRow + 6;
                c = box.maxCol - 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //9
                r = box.minRow + 6;
                c = box.maxCol - 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //10
                r = box.minRow + 6;
                c = box.maxCol - 4;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //middle ones
                //11
                r = box.minRow + 7;
                c = box.maxCol - 2;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //12
                r = box.minRow + 7;
                c = box.maxCol - 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //13
                r = box.minRow + 7;
                c = box.maxCol - 4;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //14
                r = box.minRow + 8;
                c = box.maxCol - 3;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };
                //15
                r = box.minRow + 9;
                c = box.maxCol - 1;
                if (report.things[r][c].type == SituationReport::SPACE)
                        return { r, c };

                /*
                   /-\/-\/-\.~~/-\/-\/-\/-\
                   /-\~,."'~~."a4>`~```"/-\
                   /-\`~'.,'~,,~``'`~'"'/-\
                   /-\,",a4>a4>,'`'"""",/-\
                   /-\'`.k2>``.k2>.".a4>/-\
                   /-\,..k2>*1>k2>..~,,'`~`
                   /-\~`.k2>`',k2>'"'''''~"
                   /-\`,'a4>a4>',~~,"a4>/-\
                   /-\.'~~`"'~,'`~'.~.',/-\
                   /-\~~~.~,"~`','~.~.",/-\
                   /-\,~",~`~`,a4>..".'~/-\
                   /-\/-\/-\'.`/-\/-\/-\/-\
                 */

        }

        //then add remaining 4 archers

        //add the 15 infantry


        return { 0, 0 };
}

lionheart::Action
lionheart::ChrisJenkins::recommendAction(Unit const & u, SituationReport sitch, Plan p)
{
        /*Fill this out with the behavior you want for your units.  Without changes
         * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/
        //return Action();


        //uc += + sizeof(Knight::STARTING_HP) + sizeof(UnitType)
        //+sizeof(std::unique_ptr<Map::Location>) + sizeof(Direction);
        //uc += sizeof(std::unique_ptr<Map::Location>) + sizeof(Direction);
        //int * hp = (int *)uc;
        //*hp = 9;
        //if(sitch.turns == 0) HPz.clear();
        if(sitch.turns == 0 && !westSide) return turn(Direction::WEST);  //turn toward enemy

        //std::cerr << "sizeof(int)" << sizeof(int) * 3 << std::endl;
        //std::cerr << "(((int *)&u) + 3): " << (((int *)&u) + 3) << std::endl;

        //std::cerr << "unitAddr: " << &u << " unit's hp: " << &(u.hp) << std::endl;

        if(p.hasAttack()) return p.attackEnemy();
        if(u.getType() == CROWN) return wait();

        return p.moveToEnemyCrown();



        return p.attackEnemy();


}

lionheart::Blazon lionheart::ChrisJenkins::getBlazon()
{
        /*Return your blazon here.  In case of conflicts preference will be given to
         * the students that have registered their blazons in class.*/
        return { Color::SABLE, Color::VERT, Style::PER_FESS, "Chris Jenkins" };
}
