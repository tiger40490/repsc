import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.jmx.export.annotation.ManagedAttribute;
import org.springframework.jmx.export.annotation.ManagedOperation;
import org.springframework.jmx.export.annotation.ManagedResource;

@ManagedResource(objectName = "bean:name=testJmxBean", description = "My Managed Bean", 
		log = true, logFile = "jmx.log", currencyTimeLimit = 15, persistPolicy = "OnUpdate", 
		persistPeriod = 200, persistLocation = "foo", persistName = "bar")
public class AnnotationTestBean {
	public static void main(String[] args) throws InterruptedException {
		ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext(
				"JMXExample.xml");
		context.getBean(String.class);
		context.start();
		while (true) {
			//System.out.println("Let's keep JVM from terminating");
			Thread.sleep(10000);
		}
	}
	private int age;
	@ManagedAttribute(description = "The Age Attribute", defaultValue = "199", 
			persistPeriod = 300, currencyTimeLimit = 1)
	public int getAge() {
		return age;
	}
	@ManagedOperation(description = "The Age Attribute") //works
	public void setAge(int age) {
		System.out.println("setAge() with " + age);
		this.age = age;
	}
}
