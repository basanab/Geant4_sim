#%%
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
# Read data from file  skipping first 10 lines 
data = pd.read_csv('mu_e_nt_mu_e_scatt_t0.csv',skiprows=12)

#check if the data frame has Nan values 
print(data.isnull().values.any())

#plot first column as x, second column as y
theta_mu = 3.14-np.arccos(data.iloc[:,3]/np.sqrt(data.iloc[:,1]**2+data.iloc[:,2]**2+data.iloc[:,3]**2))
theta_e = 3.14-np.arccos(data.iloc[:,6]/np.sqrt(data.iloc[:,4]**2+data.iloc[:,5]**2+data.iloc[:,6]**2))

# plt.hist(np.arccos(data.iloc[:,3]/np.sqrt(data.iloc[:,1]**2+data.iloc[:,2]**2+data.iloc[:,3]**2)),bins=100)
# plt.show()
# plt.hist(np.arccos(data.iloc[:,6]/np.sqrt(data.iloc[:,4]**2+data.iloc[:,5]**2+data.iloc[:,6]**2)),bins=100)

plt.scatter(theta_e,theta_mu)
# Give x axis label for the plot


# Show the plot on the screen
plt.show()

# %%
