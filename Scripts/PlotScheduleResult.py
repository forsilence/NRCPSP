import pandas as pd
import matplotlib.pyplot as plt

def load_data(filename,sep):
  data = pd.read_csv(filename,sep=sep)
  return data

if __name__ == '__main__':
  path = "./data/j120.sm.rs/j1201_1.sm.csv"
  data = load_data(path,sep=" ")
  keys = data.keys
  print