public class LinearSearch {
    //使用private修飾Constructor--->強制讓Linear Search 類 無法被創立 物件
    private LinearSearch() {

    }

    //泛型 線性查找的target在data陣列中的索引值，查無則回傳-1
    public static <E> int search(E[] data, E target) {
        for (int i = 0; i < data.length; i++) {
            if (data[i].equals(target)) { //調用equals來判斷 類物件
                return i;
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        int n=10000;
        Integer[] data = ArrayGenerator.generateOrderedArray(n);

        long startTime=System.nanoTime();
        int res = LinearSearch.search(data, n);
        long endTime=System.nanoTime();
        double time=(endTime-startTime)/1000000000.0;
        System.out.println("耗時: "+time+"秒");

        int res2 = LinearSearch.search(data, 666);
        System.out.println("Index: " + res2);

        Student[] students = {new Student("Alice"), new Student("Peter"), new Student("Tom")};
        Student peter = new Student("Peter");

        int res3=LinearSearch.search(students, peter);
        System.out.println(res3);
    }
}


