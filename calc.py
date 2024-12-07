import numpy as np

# Define function to calculate interstitial residue
def calculate_interstitial_residue(S, W, D, F):
    """
    Calculate the interstitial residue.
    
    Parameters:
    S (list of lists): Residual substances affecting residue, where S[i][j] is the substance from source j in space i
    W (list): Weights of the sources
    D (list of lists): Detrimental effects or removal factors, where D[i][k] is the effect from source k in space i
    F (list): Frequency or intensity of the detrimental effects
    
    Returns:
    list: Interstitial residue for each space
    """
    
    # Convert lists to numpy arrays for easier manipulation
    S = np.array(S)
    W = np.array(W)
    D = np.array(D)
    F = np.array(F)
    
    # Calculate residue contribution
    residue_contribution = np.dot(S, W)
    
    # Calculate residue removal
    residue_removal = np.dot(D, F)
    
    # Calculate interstitial residue
    residue = residue_contribution - residue_removal
    
    return residue.tolist()

# Example input data
# Residual substances affecting residue (spaces x sources)
S = [
    [5, 3, 2],  # Space 1
    [4, 2, 1],  # Space 2
    [6, 5, 3]   # Space 3
]

# Weights of the sources
W = [1.2, 0.8, 1.0]

# Detrimental effects or removal factors (spaces x sources)
D = [
    [1, 0.5, 0.2],  # Space 1
    [0.8, 0.3, 0.1],  # Space 2
    [1.1, 0.6, 0.3]   # Space 3
]

# Frequency or intensity of the detrimental effects
F = [0.9, 0.7, 0.5]

# Calculate interstitial residue
residue = calculate_interstitial_residue(S, W, D, F)
print("Interstitial Residue for each space:", residue)
