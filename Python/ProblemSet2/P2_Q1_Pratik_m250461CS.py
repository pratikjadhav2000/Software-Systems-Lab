import urllib.request
import urllib.error

def validate_url():
    url = input("Enter a URL: ")

    valid_extensions = (".com", ".org", ".in")

    try:
        # Check protocol
        if not (url.startswith("http://") or url.startswith("https://")):
            raise ValueError("URL must start with http:// or https://")

        # Remove protocol and extract domain part
        without_protocol = url.split("://", 1)[1]
        domain = without_protocol.split("/", 1)[0]

        # Check domain contains '.' and valid extension
        if "." not in domain:
            raise ValueError("Domain must contain a dot")

        if not domain.endswith(valid_extensions):
            raise ValueError("Invalid domain extension")

    except ValueError as e:
        print("Invalid URL")
        # Optional: print(e)  # to see detailed error
    else:
        print("Valid URL")
    finally:
        print("URL validation complete.\n")

def download_web_file():
    url = input("Enter URL of a web file (e.g., an HTML page): ")

    try:
        response = urllib.request.urlopen(url)  # may raise URLError / HTTPError
        data = response.read()  # bytes

    except urllib.error.HTTPError as e:
        print("HTTP error while accessing the file.")
        with open("error_log.txt", "a", encoding="utf-8") as f:
            f.write(f"HTTPError for {url}: {e}\n")
    except urllib.error.URLError as e:
        print("URL error (domain not found or invalid).")
        with open("error_log.txt", "a", encoding="utf-8") as f:
            f.write(f"URLError for {url}: {e}\n")
    else:
        # Success: save contents
        with open("output.html", "wb") as f:
            f.write(data)

        print("File downloaded and saved as output.html")
        # Display a portion of saved data
        text_sample = data[:500].decode(errors="ignore")
        print("\n--- First 500 characters of the file ---")
        print(text_sample)
        print("----------------------------------------\n")
    finally:
        print("Web file access process complete.\n")

def manage_student_scores():
    # Initial dictionary
    student_scores = {
        101: 89.5,
        102: 76.0,
        103: 91.0,
        104: 64.5,
        105: 88.0
    }

    try:
        # Optional: ask if user wants to add another student
        choice = input("Do you want to add a new student? (y/n): ").strip().lower()
        if choice == "y":
            if len(student_scores) >= 5:
                raise OverflowError("Maximum of 5 students allowed.")
            new_id_str = input("Enter new student ID (integer): ")
            new_score_str = input("Enter new student score (float): ")
            new_id = int(new_id_str)        # can raise ValueError
            new_score = float(new_score_str)  # can raise ValueError
            student_scores[new_id] = new_score
            print("New student added.")

        # Ask for ID to look up
        id_str = input("Enter a student ID to search: ")
        sid = int(id_str)  # may raise ValueError

        if sid not in student_scores:
            raise KeyError("Student ID not found.")

        print(f"Score of student {sid}: {student_scores[sid]}")

    except OverflowError as e:
        print("Error:", e)
    except ValueError:
        print("Invalid input: ID must be integer, score must be numeric.")
    except KeyError as e:
        print("Error:", e)
    finally:
        print("\nCurrent student dictionary:")
        print(student_scores)
        print()

def evaluate_expression():
    expr = input("Enter a mathematical expression (digits and + - * / only): ")

    allowed_operators = set("+-*/")

    try:
        # Check each character
        for ch in expr:
            if not (ch.isdigit() or ch in allowed_operators):
                raise TypeError(f"Invalid character found: {ch}")

        # Evaluate expression
        result = eval(expr)  # may raise ZeroDivisionError etc.
        print("Result:", result)

    except TypeError as e:
        print("Error:", e)
    except ZeroDivisionError:
        print("Error: Division by zero is not allowed.")
    finally:
        print("Expression evaluation complete.\n")

