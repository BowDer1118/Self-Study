public class ArrayGenerator {
    private ArrayGenerator(){}
    //傳入要生成的數值
    public static Integer[] generateOrderedArray(int n){
        Integer[] arr=new Integer[n];
        for (int i = 0; i < arr.length; i++) {
            arr[i]=i;
        }
        return arr;
    }
}
