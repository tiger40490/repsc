package com.iv.iterate;
/**A simple test to filter out " -* "
*/
class FilterNegative<E> implements IObjectTest<E> {//v1
	/**A simple implementation of the interface
	 * <ul>
	 * <li>return false if the argument's toString() starts with "-"
	 * <li>return false if argument is null
	 * <li>otherwise return true;
	 * </ul>
	 * Stateless and immutable. Thread-safe as a result.
	 */
	@Override
	public boolean test(E nullAbleObj) {
		if (nullAbleObj==null) return false;
		String s = nullAbleObj.toString();
		if (s == null) return false;
		if (s.startsWith("-")) {
			return false;
		}
		return true;
	}
}
