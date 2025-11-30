# P2_Pratik_M250461CS.py
# CS6103E Software Systems Laboratory - Python Programming Assignment

import pandas as pd

def read_population_data():
    """Read the world population dataset"""
    try:
        df = pd.read_csv('world_population.csv')
        print("Dataset loaded successfully!")
        print(f"Dataset shape: {df.shape}")
        return df
    except FileNotFoundError:
        print("Error: world_population.csv file not found!")
        return None

def most_populated_2022(df):
    """Find the 3 most populated countries in 2022"""
    print("\n" + "="*50)
    print("3 MOST POPULATED COUNTRIES IN 2022")
    print("="*50)
    
    # Sort by 2022 population in descending order and get top 3
    most_populated = df.nlargest(3, '2022 Population')[['Country', '2022 Population']]
    
    for idx, row in most_populated.iterrows():
        country = row['Country']
        population = row['2022 Population']
        print(f"{idx + 1}. {country}: {population:,}")
    
    return most_populated

def least_populated_2022(df):
    """Find the 3 least populated countries in 2022"""
    print("\n" + "="*50)
    print("3 LEAST POPULATED COUNTRIES IN 2022")
    print("="*50)
    
    # Sort by 2022 population in ascending order and get top 3
    least_populated = df.nsmallest(3, '2022 Population')[['Country', '2022 Population']]
    
    for idx, row in least_populated.iterrows():
        country = row['Country']
        population = row['2022 Population']
        print(f"{idx + 1}. {country}: {population:,}")
    
    return least_populated

def calculate_growth_rate(df):
    """Calculate population growth rate between 2000 and 2022"""
    print("\n" + "="*50)
    print("CALCULATING POPULATION GROWTH RATE (2000-2022)")
    print("="*50)
    
    # Calculate growth rate: (2022_pop - 2000_pop) / 2000_pop
    df['New_Growth_Rate'] = (df['2022 Population'] - df['2000 Population']) / df['2000 Population']
    
    # Display some sample growth rates
    sample_countries = df[['Country', '2000 Population', '2022 Population', 'New_Growth_Rate']].head(10)
    print("Sample growth rates for first 10 countries:")
    print(sample_countries.to_string(index=False))
    
    return df

def continent_population_2022(df):
    """Find population of each continent in 2022 and sort by increasing order"""
    print("\n" + "="*50)
    print("CONTINENT POPULATION IN 2022 (SORTED ASCENDING)")
    print("="*50)
    
    # Group by continent and sum 2022 population
    continent_pop = df.groupby('Continent')['2022 Population'].sum().sort_values()
    
    for continent, population in continent_pop.items():
        print(f"{continent}: {population:,}")
    
    return continent_pop

def classify_countries(df):
    """Classify countries based on 2022 population into categories"""
    print("\n" + "="*50)
    print("CLASSIFYING COUNTRIES BY 2022 POPULATION")
    print("="*50)
    
    # Initialize the new column
    df['Category_2022'] = ''
    
    categories_count = {'Small': 0, 'Medium': 0, 'Large': 0, 'Mega': 0, 'Missing': 0}
    
    # Using for loop to iterate through each row
    for index, row in df.iterrows():
        pop_2022 = row['2022 Population']
        
        # Check for missing or invalid values
        if pd.isna(pop_2022) or pop_2022 <= 0:
            category = 'Missing'
        else:
            if pop_2022 < 10000000:  # Less than 10 million
                category = 'Small'
            elif pop_2022 <= 100000000:  # Between 10M and 100M
                category = 'Medium'
            elif pop_2022 <= 500000000:  # Between 100M and 500M
                category = 'Large'
            else:  # More than 500 million
                category = 'Mega'
        
        df.at[index, 'Category_2022'] = category
        categories_count[category] += 1
    
    # Display category counts
    print("Category distribution:")
    for category, count in categories_count.items():
        print(f"{category}: {count} countries")
    
    # Display first 10 rows with required columns
    print("\nFirst 10 rows with classification:")
    display_columns = ['Country', '2022 Population', 'Category_2022']
    first_10 = df[display_columns].head(10)
    print(first_10.to_string(index=False))
    
    return df

def continent_year_query(df):
    """Query population details by continent and year"""
    print("\n" + "="*50)
    print("CONTINENT AND YEAR POPULATION QUERY")
    print("="*50)
    
    # Get user input
    continent = input("Enter Continent Name (e.g., Asia, Europe, Africa): ").strip()
    year = input("Enter Year (e.g., 2000, 2010, 2022): ").strip()
    
    # Validate continent
    valid_continents = df['Continent'].unique()
    if continent not in valid_continents:
        print(f"Error: Continent '{continent}' not found in dataset.")
        print(f"Valid continents: {', '.join(valid_continents)}")
        return
    
    # Validate year column
    year_column = f"{year} Population"
    if year_column not in df.columns:
        print(f"Error: Year '{year}' data not available in dataset.")
        print(f"Available years: 1970, 1980, 1990, 2000, 2010, 2015, 2020, 2022")
        return
    
    # Filter data for the specified continent and year
    continent_data = df[df['Continent'] == continent]
    
    if continent_data.empty:
        print(f"No data found for continent: {continent}")
        return
    
    # Sort by population in descending order for better display
    continent_data = continent_data.sort_values(year_column, ascending=False)
    
    # Calculate total population
    total_population = continent_data[year_column].sum()
    
    # Display results
    print(f"\n| {'Country':<25} | {year:>15} |")
    print(f"|{'-'*27}|{'-'*17}|")
    
    for _, row in continent_data.iterrows():
        country = row['Country']
        population = row[year_column]
        print(f"| {country:<25} | {population:>15,} |")
    
    print(f"\n---Total Population of {continent} in {year}: {total_population:,}")
    
    return continent_data, total_population

def main():
    """Main function to execute all tasks"""
    print("CS6103E Software Systems Laboratory - Python Programming Assignment")
    print("WORLD POPULATION DATA ANALYSIS")
    print("="*60)
    
    # Read the dataset
    df = read_population_data()
    
    if df is None:
        return
    
    try:
        # Question 1 tasks
        print("\nQUESTION 1 TASKS:")
        print("="*40)
        
        # i. Most and least populated countries
        most_populated = most_populated_2022(df)
        least_populated = least_populated_2022(df)
        
        # ii. Growth rate calculation
        df = calculate_growth_rate(df)
        
        # iii. Continent population
        continent_pop = continent_population_2022(df)
        
        # iv. Country classification
        df = classify_countries(df)
        
        # Question 2 - Interactive query
        print("\nQUESTION 2: INTERACTIVE CONTINENT-YEAR QUERY")
        print("="*50)
        
        while True:
            continent_year_query(df)
            
            # Ask if user wants to continue
            continue_query = input("\nDo you want to make another query? (yes/no): ").strip().lower()
            if continue_query not in ['yes', 'y']:
                break
        
        print("\n" + "="*60)
        print("ASSIGNMENT COMPLETED SUCCESSFULLY!")
        print("="*60)
        
    except Exception as e:
        print(f"Error during execution: {e}")

if __name__ == "__main__":
    main()