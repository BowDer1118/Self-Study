import com.bowder.junit.Calculator;
import org.junit.Test;

//測試Calculator類的測試類
public class CalculatorTest {
    private Calculator cal=new Calculator();
    //測試用例通常會在原方法前面加入test
    @Test
    public void testAdd(){
        int result=cal.add(1,2);
        System.out.println(result);
    }
    @Test
    public void testSubtract(){
        int result=cal.subtract(1,2);
        System.out.println(result);
    }
    @Test
    public void testMultiply(){
        int result=cal.multiply(1,2);
        System.out.println(result);
    }
    @Test
    public void testDivide(){
        double result=cal.divide(1,2);
        System.out.println(result);
    }

    @Test
    public void testDivide2(){
        double result=cal.divide(1,0);
        System.out.println(result);
    }
}
