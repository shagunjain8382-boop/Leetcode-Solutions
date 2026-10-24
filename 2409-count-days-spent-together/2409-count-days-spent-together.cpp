class Solution {
public:
  int dayofYear(string date){
    int days[] = {31, 28, 31, 30, 31, 30,
                      31, 31, 30, 31, 30, 31};
      int month = stoi(date.substr(0, 2));
        int day = stoi(date.substr(3, 2));
        int total=day;
        for(int i=0;i<month-1;i++){
            total+=days[i];
        }
        return total;
  }
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
     string start=max(arriveAlice,arriveBob);
     string end=min(leaveAlice,leaveBob);
     int startDay=dayofYear(start);
     int endDay=dayofYear(end);
     if(startDay>endDay){
        return 0;
     }
     return endDay-startDay+1;
    }
};