
#include <iostream>
#include <Windows.h>

class BusStop
{
private:
    unsigned int morningMTPas;
    unsigned int morningMTBus;
    unsigned int dayMTPas;
    unsigned int dayMTBus;
    unsigned int eveningMTPas;
    unsigned int eveningMTBus;
    bool end;
public:
    BusStop()
    {
        morningMTPas = 0;
        morningMTBus = 0;
        dayMTPas = 0;
        dayMTBus = 0;
        eveningMTPas = 0;
        eveningMTBus = 0;
        end = false;
    }
    BusStop(unsigned int _morningMTPas, unsigned int _morningMTBus, unsigned int _dayMTPas, unsigned int _dayMTBus,
        unsigned int _eveningMTPas, unsigned int _eveningMTBus, bool _end)
    {
        morningMTPas = _morningMTPas;
        morningMTBus = _morningMTBus;
        dayMTPas = _dayMTPas;
        dayMTBus = _dayMTBus;
        eveningMTPas = _eveningMTPas;
        eveningMTBus = _eveningMTBus;
        end = _end;
    }

    int morningMT()
    {
        return float(morningMTPas < morningMTBus ? (morningMTBus - morningMTPas) / 2 : (morningMTPas - morningMTBus) / 2);
    }
    int dayMT()
    {
        return float(dayMTPas < dayMTBus ? (dayMTBus - dayMTPas) / 2 : (dayMTPas - dayMTBus) / 2);
    }
    int eveningMT()
    {
        return float(eveningMTPas < eveningMTBus ? (eveningMTBus - eveningMTPas) / 2 : (eveningMTPas - eveningMTBus) / 2);
    }

    int interval(unsigned int numOfPeople, unsigned int Morning_Day_Evening_1_3)
    {
        if (Morning_Day_Evening_1_3 == 1)
        {
            return morningMTPas * numOfPeople;
        }
        else if (Morning_Day_Evening_1_3 == 2)
        {
            return dayMTPas * numOfPeople;
        }
        else if (Morning_Day_Evening_1_3 == 3)
        {
            return eveningMTPas * numOfPeople;
        }
        else
        {
            return -1;
        }
    }

    void copy(BusStop& obj)
    {
        this->morningMTPas = obj.morningMTPas;
        std::cout << "copy: " << obj.morningMTPas << '\n';
        this->morningMTBus = obj.morningMTBus;
        this->dayMTPas = obj.dayMTPas;
        this->dayMTBus = obj.dayMTBus;
        this->eveningMTPas = obj.eveningMTPas;
        this->eveningMTBus = obj.eveningMTBus;
        this->end = obj.end;
    }

    unsigned int getMorningMTPas() const
    {
        return morningMTPas;
    }
    void setMorningMTPas(unsigned int _morningMTPas)
    {
        this->morningMTPas = _morningMTPas;
    }
    unsigned int getMorningMTBus() const
    {
        return morningMTBus;
    }
    void setMorningMTBus(unsigned int _morningMTBus)
    {
        this->morningMTBus = _morningMTBus;
    }
    unsigned int getDayMTPas() const
    {
        return dayMTPas;
    }
    void setDayMTPas(unsigned int _dayMTPas)
    {
        this->dayMTPas = _dayMTPas;
    }
    unsigned int getDayMTBus() const
    {
        return dayMTBus;
    }
    void setDayMTBus(unsigned int _dayMTBus)
    {
        this->dayMTBus = _dayMTBus;
    }
    unsigned int getEveningMTPas() const
    {
        return eveningMTPas;
    }
    void setEveningMTPas(unsigned int _eveningMTPas)
    {
        this->eveningMTPas = _eveningMTPas;
    }
    unsigned int getEveningMTBus() const
    {
        return eveningMTBus;
    }
    void setEveningMTBus(unsigned int _eveningMTBus)
    {
        this->eveningMTBus = _eveningMTBus;
    }
    bool getEnd() const
    {
        return end;
    }
    void setEnd(bool _end)
    {
        this->end = _end;
    }
};
class BSQueue
{
private:
    BusStop* queue;
    unsigned int size;
    int endIndx;
    int startIndx;
public:
    BSQueue()
    {
        size = 0;
        queue = nullptr;
        endIndx = -1;
        startIndx = 0;
    }
    BSQueue(unsigned int _size)
    {
        size = _size;
        queue = new BusStop[size];
        endIndx = -1;
        startIndx = 0;
    }

    void add(BusStop& obj)
    {
        if (full())
        {
            grow(this->size + 1);
        }
        ++endIndx;
        queue[endIndx].copy(obj);
    }
    BusStop& pop()
    {
        if (queue != nullptr && startIndx - 1 != endIndx)
        {
            return queue[startIndx++];
        }
        BusStop trash;
        return trash;
    }
    BusStop& get()
    {
        if (queue != nullptr && startIndx - 1 != endIndx)
        {
            return queue[startIndx];
        }
        BusStop trash;
        return trash;
    }

    bool full()
    {
        if (endIndx < size - 1 && queue != nullptr || endIndx == -1)
        {
            return false;
        }
        return true;
    }

    void grow(unsigned int _size, int grow = 5)
    {
        if (_size > this->size)
        {
            BusStop* temp = new BusStop[this->size + grow];
            if (queue != nullptr)
            {
                for (int i = 0; i - 1 != endIndx; i++)
                {
                    temp[i].copy(queue[i]);
                }
                delete[] queue;
            }
            queue = temp;
            this->size += grow;
            temp = nullptr;
        }
        else
        {
            freeExtra();
        }
    }
    void freeExtra()
    {
        if (queue != nullptr)
        {
            BusStop* temp = new BusStop[endIndx - startIndx + 1];
            for (int i = startIndx; i - 1 != endIndx; i++)
            {
                temp[i - startIndx].copy(queue[i]);
            }
            delete[] queue;
            queue = temp;
            this->size = endIndx - startIndx + 1;
            startIndx = 0;
            temp = nullptr;
        }
    }
    void del()
    {
        size = 0;
        endIndx = -1;
        startIndx = 0;
        delete[] queue;
        queue = nullptr;
    }

    ~BSQueue()
    {
        if (queue != nullptr)
        {
            delete[] queue;
        }
    }
};

struct person
{
    int number = -1;
    int priority = -1;
};
struct stats
{
    int number = -1;
    unsigned long long giveTime = time(0);

    void print()
    {
        std::cout << "Person number: " << number << '\n';
        std::cout << "Year: " << giveTime / 31449600 + 1969 << "; " << "Month: " << giveTime % 31449600 / 2592000 << "; " <<
            "Day: " << giveTime % 31449600 % 2592000 /  86400 << "; " << "Hours: " << giveTime % 31449600 % 2592000 % 86400 / 3600 << 
            "; " << "Minuts: " << giveTime % 31449600 % 2592000 % 86400 % 3600 / 60 << "; " 
            << "Seconds: " << giveTime % 31449600 % 2592000 % 86400 % 3600 % 60 << '\n';
    }
};
class Printer
{
private:
    person* queue;
    unsigned int size;
    int endIndx;
    int startIndx;
public:
    Printer()
    {
        queue = nullptr;
        size = 0;
        endIndx = -1;
        startIndx = 0;
    }
    Printer(unsigned int _size)
    {
        size = _size;
        queue = new person[size];
        endIndx = -1;
        startIndx = 0;
    }


    void add(person& obj)
    {
        if (full())
        {
            grow(this->size + 1);
        }
        ++endIndx;
        this->queue[endIndx].number = obj.number;
        this->queue[endIndx].priority = obj.priority;
        sort();
    }
    person& pop()
    {
        if (queue != nullptr && startIndx - 1 != endIndx)
        {
            return this->queue[startIndx++];
        }
        person trash;
        return trash;
    }
    person& get()
    {
        if (queue != nullptr && startIndx - 1 != endIndx)
        {
            return queue[startIndx];
        }
        person trash;
        return trash;
    }

    bool full()
    {
        if (endIndx < size - 1 && queue != nullptr || endIndx == -1)
        {
            return false;
        }
        return true;
    }

    void sort()
    {
        person temp;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                if (queue[j].priority < queue[j + 1].priority)
                {
                    temp.number = queue[j + 1].number;
                    temp.priority = queue[j + 1].priority;
                    queue[j + 1].number = queue[j].number;
                    queue[j + 1].priority = queue[j].priority;
                    queue[j].number = temp.number;
                    queue[j].priority = temp.priority;
                }
            }
        }
    }
    void grow(unsigned int _size, int grow = 5)
    {
        if (_size > this->size)
        {
            person* temp = new person[this->size + grow];
            if (queue != nullptr)
            {
                for (int i = 0; i - 1 != endIndx; i++)
                {
                    temp[i].number = queue[i].number;
                    temp[i].priority = queue[i].priority;
                }
                delete[] queue;
            }
            queue = temp;
            this->size += grow;
            temp = nullptr;
        }
        else
        {
            freeExtra();
        }
    }
    void freeExtra()
    {
        if (queue != nullptr)
        {
            person* temp = new person[endIndx - startIndx + 1];
            for (int i = startIndx; i - 1 != endIndx; i++)
            {
                temp[i - startIndx].number = queue[i].number;
                temp[i - startIndx].priority = queue[i].priority;
            }
            delete[] queue;
            queue = temp;
            this->size = endIndx - startIndx + 1;
            startIndx = 0;
            temp = nullptr;
        }
    }
    void del()
    {
        size = 0;
        endIndx = -1;
        startIndx = 0;
        delete[] queue;
        queue = nullptr;
    }

    ~Printer()
    {
        std::cout << "\ndeleted\n";
        if (queue != nullptr)
        {
            delete[] queue;
        }
    }
};
class Statistic
{
private:
    stats* queue;
    unsigned int size;
    int endIndx;
    int startIndx;
public:
    Statistic()
    {
        queue = nullptr;
        size = 0;
        endIndx = -1;
        startIndx = 0;
    }
    Statistic(int _size)
    {
        size = _size;
        queue = new stats[size];
        endIndx = -1;
        startIndx = 0;
    }

    void add(stats& obj)
    {
        if (full())
        {
            grow(this->size + 1);
        }
        ++endIndx;
        this->queue[endIndx].number = obj.number;
        this->queue[endIndx].giveTime = obj.giveTime;
    }
    stats& pop()
    {
        if (queue != nullptr && startIndx - 1 != endIndx)
        {
            return queue[startIndx++];
        }
        stats trash;
        return trash;
    }
    stats& get()
    {
        if (queue != nullptr && startIndx - 1 != endIndx)
        {
            return queue[startIndx];
        }
        stats trash;
        return trash;
    }

    bool full()
    {
        if (endIndx < size - 1 && queue != nullptr || endIndx == -1)
        {
            return false;
        }
        return true;
    }

    void grow(unsigned int _size, int grow = 5)
    {
        if (_size > this->size)
        {
            stats* temp = new stats[this->size + grow];
            if (queue != nullptr)
            {
                for (int i = 0; i - 1 != endIndx; i++)
                {
                    temp[i].number = queue[i].number;
                    temp[i].giveTime = queue[i].giveTime;
                }
                delete[] queue;
            }
            queue = temp;
            this->size += grow;
            temp = nullptr;
        }
        else
        {
            freeExtra();
        }
    }
    void freeExtra()
    {
        if (queue != nullptr)
        {
            stats* temp = new stats[endIndx - startIndx + 1];
            for (int i = startIndx; i - 1 != endIndx; i++)
            {
                temp[i - startIndx].number = queue[i].number;
                temp[i - startIndx].giveTime = queue[i].giveTime;
            }
            delete[] queue;
            queue = temp;
            this->size = endIndx - startIndx + 1;
            startIndx = 0;
            temp = nullptr;
        }
    }
    void del()
    {
        size = 0;
        endIndx = -1;
        startIndx = 0;
        delete[] queue;
        queue = nullptr;
    }

    ~Statistic()
    {
        if (queue != nullptr)
        {
            delete queue;
        }
    }
};

int main()
{
    int choise = -1;
    int size = 10;
    Printer tester(size);
    Statistic helper(size);
    while (choise != 0)
    {
        std::cout << "choose:\n1 - Bus stop queue(pop/interval);\n2 - Printer queue;\n0 - exit;\n";
        std::cin >> choise;
        if (choise == 1)
        {
            BusStop bus;
            BSQueue tester(size);
            for (int i = 0; i < size; i++)
            {
                bus.setMorningMTPas(i);
                bus.setMorningMTBus(i * 2);
                bus.setDayMTPas(i + 1);
                bus.setDayMTBus((i + 1) * 2);
                bus.setEveningMTPas(i + 2);
                bus.setEveningMTBus((i + 2) * 2);
                bus.setEnd(false);
                tester.add(bus);
            }
            std::cout << tester.get().getDayMTPas() << '\n';
            std::cout << tester.get().getDayMTBus() << '\n';
            std::cout << tester.pop().interval(20, 2) << '\n';
        }
        else if (choise == 2)
        {
            std::cout << "1 - add new person to queue;\n2 - pop person from queue;\n3 - get person from queue;\n4 - show stat;\n0 - exit;\n";
            std::cin >> choise;
            if (choise == 1)
            {
                person temp;
                std::cout << "Enter person number: ";
                std::cin >> temp.number;
                std::cout << "Enter person priority: ";
                std::cin >> temp.priority;
                tester.add(temp);
            }
            else if (choise == 2)
            {
                person temp;
                stats obj;
                temp.number = tester.get().number;
                temp.priority = tester.pop().priority;
                obj.number = temp.number;
                obj.giveTime = time(0);
                helper.add(obj);
                std::cout << "number: " << temp.number << '\n' << "priority: " << temp.priority << '\n';
            }
            else if (choise == 3)
            {
                person temp;
                temp.number = 1;
                std::cout << "here: " << tester.get().number << '\n';
                temp.number = tester.get().number;
                temp.priority = tester.get().priority;
                std::cout << "number: " << temp.number << '\n' << "priority: " << temp.priority << '\n';
            }
            else if (choise == 4)
            {
                helper.pop().print();
            }
        }
    }
}