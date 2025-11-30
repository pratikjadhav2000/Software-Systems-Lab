# P1_Pratik_M250461CS.py
# CS6103E Software Systems Laboratory - Python Programming Assignment

import pandas as pd
import re

def question1():
    """Question 1: Titanic dataset operations"""
    print("=" * 50)
    print("QUESTION 1: TITANIC DATASET OPERATIONS")
    print("=" * 50)
    
    # Read the CSV file
    titanic = pd.read_csv('tested.csv')
    
    # i. Display shape and column information
    print("\n1.i. Dataset Information:")
    print(f"Shape of dataset: {titanic.shape}")
    print(f"Number of rows: {titanic.shape[0]}")
    print(f"Number of columns: {titanic.shape[1]}")
    print("\nColumn names and data types:")
    print(titanic.dtypes)
    
    # ii. Handle missing values
    print("\n1.ii. Handling Missing Values:")
    print(f"Before cleaning - Rows: {titanic.shape[0]}, Columns: {titanic.shape[1]}")
    
    # Identify columns with missing values
    missing_data = titanic.isnull().sum()
    print("\nMissing values per column:")
    print(missing_data[missing_data > 0])
    
    # Delete columns with more than 50% missing values
    total_rows = len(titanic)
    columns_to_drop = []
    for column in titanic.columns:
        missing_count = titanic[column].isnull().sum()
        if missing_count > total_rows * 0.5:
            columns_to_drop.append(column)
    
    if columns_to_drop:
        titanic_cleaned = titanic.drop(columns=columns_to_drop)
        print(f"Dropped columns with >50% missing values: {columns_to_drop}")
    else:
        titanic_cleaned = titanic.copy()
    
    # Remove rows with any missing values
    titanic_cleaned = titanic_cleaned.dropna()
    print(f"After cleaning - Rows: {titanic_cleaned.shape[0]}, Columns: {titanic_cleaned.shape[1]}")
    
    # Save cleaned dataframe
    titanic_cleaned.to_csv('cleaned.csv', index=False)
    print("Cleaned dataset saved as 'cleaned.csv'")
    
    # iii. Replace missing values in original dataset
    print("\n1.iii. Replacing Missing Values:")
    titanic_replaced = titanic.copy()
    
    # Replace Age and Fare with mean
    if 'Age' in titanic_replaced.columns:
        age_mean = titanic_replaced['Age'].mean()
        titanic_replaced['Age'].fillna(age_mean, inplace=True)
        print(f"Replaced missing Age values with mean: {age_mean:.2f}")
    
    if 'Fare' in titanic_replaced.columns:
        fare_mean = titanic_replaced['Fare'].mean()
        titanic_replaced['Fare'].fillna(fare_mean, inplace=True)
        print(f"Replaced missing Fare values with mean: {fare_mean:.2f}")
    
    # Replace Cabin with 'Unknown'
    if 'Cabin' in titanic_replaced.columns:
        titanic_replaced['Cabin'].fillna('Unknown', inplace=True)
        print("Replaced missing Cabin values with 'Unknown'")
    
    return titanic

def question2(titanic):
    """Question 2: Name formatting and unique IDs"""
    print("\n" + "=" * 50)
    print("QUESTION 2: NAME FORMATTING AND UNIQUE IDs")
    print("=" * 50)
    
    # Create a copy to avoid modifying original
    df = titanic.copy()
    
    # i. Reformat names
    print("\n2.i. Name Formatting:")
    
    def format_name(name):
        """Convert 'LastName, Title. FirstName' to 'Title FirstName LastName'"""
        try:
            # Handle names with quotes and special characters
            name = str(name).replace('"', '').replace("'", "")
            
            # Pattern to match "LastName, Title. FirstName" or variations
            pattern = r'([^,]+),\s*([^\.]+)\.\s*(.+)'
            match = re.match(pattern, name)
            
            if match:
                last_name = match.group(1).strip()
                title = match.group(2).strip()
                first_name = match.group(3).strip()
                return f"{title}. {first_name} {last_name}"
            else:
                return name
        except:
            return name
    
    df['Formatted Name'] = df['Name'].apply(format_name)
    
    print("First 10 records with formatted names:")
    print(df[['Name', 'Formatted Name']].head(10).to_string(index=False))
    
    # ii. Create unique IDs and dictionary
    print("\n2.ii. Unique IDs and Dictionary:")
    
    passenger_dict = {}
    
    for index, row in df.iterrows():
        # Create unique ID: P{row_number+1}_{Pclass}
        passenger_id = f"P{index+1}_{row['Pclass']}"
        
        # Store passenger details
        passenger_dict[passenger_id] = [row['Name'], row['Pclass'], row['Fare']]
    
    print(f"Created dictionary with {len(passenger_dict)} passengers")
    
    # Display top 5 passengers with highest fare
    print("\nTop 5 passengers with highest fare:")
    
    # Convert dictionary to list for sorting
    passenger_list = []
    for pid, details in passenger_dict.items():
        passenger_list.append({
            'ID': pid,
            'Name': details[0],
            'Pclass': details[1],
            'Fare': details[2]
        })
    
    # Sort by fare in descending order and get top 5
    top_passengers = sorted(passenger_list, key=lambda x: x['Fare'], reverse=True)[:5]
    
    print("\n| Name | Pclass | Fare |")
    print("|------|--------|------|")
    for passenger in top_passengers:
        name = passenger['Name'][:30] + "..." if len(passenger['Name']) > 30 else passenger['Name']
        print(f"| {name} | {passenger['Pclass']} | {passenger['Fare']:.4f} |")
    
    return df, passenger_dict

def question3():
    """Question 3: Text file processing"""
    print("\n" + "=" * 50)
    print("QUESTION 3: TEXT FILE PROCESSING")
    print("=" * 50)
    
    # Read the text file
    with open('data.txt', 'r') as file:
        text_content = file.read()
    
    print("Original text content:")
    print(text_content[:100] + "..." if len(text_content) > 100 else text_content)
    
    # i. Extract numeric codes
    print("\n3.i. Numeric Codes:")
    numeric_codes = re.findall(r'\d+', text_content)
    print(f"Codes: {numeric_codes}")
    
    # ii. Extract words ending with numbers
    print("\n3.ii. Words ending with numbers:")
    words_with_numbers = re.findall(r'[a-zA-Z_]+?\d+', text_content)
    print(f"Words with numbers at end: {' '.join(words_with_numbers)}")
    
    # iii. Identify uppercase words
    print("\n3.iii. Uppercase words:")
    uppercase_words = re.findall(r'\b[A-Z]+\b', text_content)
    print(f"Uppercase words: {' '.join(uppercase_words)}")
    
    # iv. Replace special characters with single space and clean text
    print("\n3.iv. Cleaned text:")
    
    # Replace all non-alphanumeric characters (except spaces) with single space
    cleaned_text = re.sub(r'[^a-zA-Z0-9\s]', ' ', text_content)
    
    # Replace multiple spaces with single space
    cleaned_text = re.sub(r'\s+', ' ', cleaned_text).strip()
    
    print(f"Cleaned text: {cleaned_text}")
    
    return {
        'numeric_codes': numeric_codes,
        'words_with_numbers': words_with_numbers,
        'uppercase_words': uppercase_words,
        'cleaned_text': cleaned_text
    }

def main():
    """Main function to execute all questions"""
    print("CS6103E Software Systems Laboratory - Python Programming Assignment")
    print("Submission: P1.<FIRST NAME>.<ROLLNO>.py")
    print("=" * 60)
    
    try:
        # Question 1
        titanic_df = question1()
        
        # Question 2
        formatted_df, passenger_dict = question2(titanic_df)
        
        # Question 3
        text_results = question3()
        
        print("\n" + "=" * 60)
        print("ASSIGNMENT COMPLETED SUCCESSFULLY!")
        print("=" * 60)
        
    except FileNotFoundError as e:
        print(f"Error: File not found - {e}")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()