def almostEqual(float1, float2):
  return abs(float2 - float1) < 0.00001
  
def annualized(years, multiYearReturn): 
  if multiYearReturn == -100: return -100
  assert multiYearReturn > -100, '-100% return means totoal loss'
  
  returnFactor = multiYearReturn/100.0 + 1
  annualizedReturnFactor = pow(returnFactor, 1.0/years)
  ret = 100* (annualizedReturnFactor - 1)
  print multiYearReturn, '% return over', years, 'years means', ret, '% is the annualized percentage return'
  assert almostEqual(multiYearReturn, (pow(ret/100+1, years)-1)*100)
  return ret

annualized(5, -10)
