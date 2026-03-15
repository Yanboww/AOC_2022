package AOC2016;
import java.util.*;
import java.io.*;
public class Day19 {
    public static void main(String[] args){
        System.out.println(greedyElf(3005290,1));
        System.out.println(greedyElf(3005290,2));
        //System.out.println(greedyElf(4,1));
    }

    public static int greedyElf(int elf, int part){
        if(part == 1) return takeLeft(elf);
        return takeAcross(elf);
    }

    public static int takeLeft(int elf){
        ArrayList<Integer> list = new ArrayList<>();
        for(int i = 1; i <= elf; i++){
            if(i%2==0) continue;
            if((elf)%2!=0 && i == 1) continue;;
            list.add(i);
        }
        while(list.size() > 1){
            ArrayList<Integer> temp = new ArrayList<>();
            elf = list.size();
            for(int i = 0; i < list.size(); i++){
                if((i+1)%2==0) continue;
                if(elf%2!=0 && i == 0) continue;
                temp.add(list.get(i));
            }
            list = temp;
        }
        return list.get(0);
    }

    public static int takeAcross(int elf){
        LinkedList<Integer> side1 = new LinkedList<>();
        LinkedList<Integer> side2 = new LinkedList<>();
        for(int i = 1; i <= elf; i++){
            if(i <= elf/2) side1.offerLast(i);
            else side2.offerLast(i);
        }
        while(side1.size() + side2.size() != 1){
            int temp = !side1.isEmpty() ?side1.pollFirst():0;
            if(side1.size() == side2.size()) side1.pollLast();
            else side2.pollFirst();
            side2.addLast(temp);
            side1.addLast(side2.pollFirst());
        }
        if(side1.size() == 1) return side1.pollFirst();
        return side2.pollFirst();
    }
}
