#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 50
#define MAX_PATIENTS 100
#define MAX_DOCTORS 50
#define MAX_PRESCRIPTION 256

// Structure for patient
struct Patient {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int age;
    char gender;
    char prescription[MAX_PRESCRIPTION];
};

// Structure for doctor
struct Doctor {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char specialization[MAX_NAME_LENGTH];
};

// Function to delete a patient from the array
void deletePatient(struct Patient patients[], int *numPatients, int index) {
    if (index < *numPatients) {
        // Shift elements to the left to overwrite the deleted patient
        for (int i = index; i < *numPatients - 1; ++i) {
            strcpy(patients[i].firstName, patients[i + 1].firstName);
            strcpy(patients[i].lastName, patients[i + 1].lastName);
            patients[i].age = patients[i + 1].age;
            patients[i].gender = patients[i + 1].gender;
            strcpy(patients[i].prescription, patients[i + 1].prescription);
        }
        (*numPatients)--;
    }
}

// Function to display all patients
void showPatients(struct Patient patients[], int numPatients) {
    printf("\nList of patients:\n");
    for (int i = 0; i < numPatients; ++i) {
        printf("%d. %s %s - Age: %d, Gender: %c\n", i + 1, patients[i].firstName, patients[i].lastName,
               patients[i].age, patients[i].gender);
        if (strlen(patients[i].prescription) > 0) {
            printf("   Prescription: %s\n", patients[i].prescription);
        } else {
            printf("   No active prescription.\n");
        }
    }
}

// Function to add prescription to a patient
void addPrescription(struct Patient *patient, char *prescription) {
    strcpy(patient->prescription, prescription);
}

// Function to delete a doctor from the array
void deleteDoctor(struct Doctor doctors[], int *numDoctors, int index) {
    if (index < *numDoctors) {
        // Shift elements to the left to overwrite the deleted doctor
        for (int i = index; i < *numDoctors - 1; ++i) {
            strcpy(doctors[i].firstName, doctors[i + 1].firstName);
            strcpy(doctors[i].lastName, doctors[i + 1].lastName);
            strcpy(doctors[i].specialization, doctors[i + 1].specialization);
        }
        (*numDoctors)--;
    }
}

// Function to display all doctors
void showDoctors(struct Doctor doctors[], int numDoctors) {
    printf("\nList of doctors:\n");
    for (int i = 0; i < numDoctors; ++i) {
        printf("%d. %s %s - Specialization: %s\n", i + 1, doctors[i].firstName, doctors[i].lastName, doctors[i].specialization);
    }
}

// Function to display prescriptions of patients
void showPrescriptions(struct Patient patients[], int numPatients) {
    printf("\nPrescriptions for patients:\n");
    for (int i = 0; i < numPatients; ++i) {
        printf("%d. %s %s:\n", i + 1, patients[i].firstName, patients[i].lastName);
        if (strlen(patients[i].prescription) > 0) {
            printf("   Prescription: %s\n", patients[i].prescription);
        } else {
            printf("   No active prescription.\n");
        }
    }
}

int main() {
    struct Patient patients[MAX_PATIENTS]; // Array to hold patients
    struct Doctor doctors[MAX_DOCTORS]; // Array to hold doctors
    int numPatients = 0; // Current number of registered patients
    int numDoctors = 0; // Current number of registered doctors

    char role[MAX_NAME_LENGTH]; // Role as a string
    int securityCode; // Security code
    bool continueProgram = true; // Variable to control program continuation

    while (continueProgram) {
        printf("\nWelcome to our hospital system.\n");
        printf("Choose the role you want to register as (doctor, patient, admin, exit): ");
        fgets(role, sizeof(role), stdin);
        role[strcspn(role, "\n")] = '\0'; // Remove newline character

        if (strcmp(role, "patient") == 0) {
            // Patient data registration
            struct Patient patient;
            printf("Registering a patient:\n");
            printf("Enter first name: ");
            fgets(patient.firstName, sizeof(patient.firstName), stdin);
            patient.firstName[strcspn(patient.firstName, "\n")] = '\0'; // Remove newline character

            printf("Enter last name: ");
            fgets(patient.lastName, sizeof(patient.lastName), stdin);
            patient.lastName[strcspn(patient.lastName, "\n")] = '\0'; // Remove newline character

            printf("Enter age: ");
            scanf("%d", &patient.age);

            printf("Enter gender (M/F): ");
            scanf(" %c", &patient.gender);

            getchar(); // Consume the newline character left by scanf

            // Adding patient to the patient list
            if (numPatients < MAX_PATIENTS) {
                patients[numPatients++] = patient;
                printf("Patient registered successfully.\n");
            } else {
                printf("Maximum patient capacity reached.\n");
            }

        } else if (strcmp(role, "doctor") == 0) {
            // Doctor data registration
            struct Doctor doctor;
            printf("\nRegistering a doctor:\n");
            printf("Enter first name of the doctor: ");
            fgets(doctor.firstName, sizeof(doctor.firstName), stdin);
            doctor.firstName[strcspn(doctor.firstName, "\n")] = '\0'; // Remove newline character

            printf("Enter last name of the doctor: ");
            fgets(doctor.lastName, sizeof(doctor.lastName), stdin);
            doctor.lastName[strcspn(doctor.lastName, "\n")] = '\0'; // Remove newline character

            printf("Enter specialization of the doctor: ");
            fgets(doctor.specialization, sizeof(doctor.specialization), stdin);
            doctor.specialization[strcspn(doctor.specialization, "\n")] = '\0'; // Remove newline character

            // Adding doctor to the doctor list
            if (numDoctors < MAX_DOCTORS) {
                doctors[numDoctors++] = doctor;
                printf("Doctor registered successfully.\n");
            } else {
                printf("Maximum doctor capacity reached.\n");
            }

        } else if (strcmp(role, "admin") == 0) {
            printf("Enter the security code: ");
            scanf("%d", &securityCode);

            if (securityCode == 2006) {
                // Admin menu
                int option;
                printf("\nAdmin options:\n");
                printf("1. Show doctors\n");
                printf("2. Show patients\n");
                printf("3. Delete patient\n");
                printf("4. Add patient prescription\n");
                printf("5. Delete doctor\n");
                printf("6. Show patient prescriptions\n");
                printf("7. Exit program\n");
                printf("Choose your option: ");
                scanf("%d", &option);

                switch (option) {
                    case 1:
                        showDoctors(doctors, numDoctors);
                        break;
                    case 2:
                        showPatients(patients, numPatients);
                        break;
                    case 3:
                        // Delete patient
                        printf("\nEnter the patient number you want to delete: ");
                        int patientIndex;
                        scanf("%d", &patientIndex);
                        if (patientIndex > 0 && patientIndex <= numPatients) {
                            deletePatient(patients, &numPatients, patientIndex - 1);
                            printf("Patient deleted successfully.\n");
                        } else {
                            printf("Invalid patient number.\n");
                        }
                        break;
                 case 4:
    // Add prescription to patient
    if (numPatients > 0) {
        printf("\nList of patients:\n");
        for (int i = 0; i < numPatients; ++i) {
            printf("%d. %s %s\n", i + 1, patients[i].firstName, patients[i].lastName);
        }

        int patientIndex;
        printf("Choose the patient number to add prescription: ");
        scanf("%d", &patientIndex);

        if (patientIndex > 0 && patientIndex <= numPatients) {
            getchar(); // Consume newline left by scanf
            printf("Enter medical prescription for %s %s: ", patients[patientIndex - 1].firstName,
                   patients[patientIndex - 1].lastName);
            fgets(patients[patientIndex - 1].prescription, sizeof(patients[patientIndex - 1].prescription), stdin);
            patients[patientIndex - 1].prescription[strcspn(patients[patientIndex - 1].prescription, "\n")] = '\0'; // Remove newline character
            printf("Prescription added successfully for %s %s.\n", patients[patientIndex - 1].firstName,
                   patients[patientIndex - 1].lastName);
        } else {
            printf("Invalid patient number.\n");
        }
    } else {
        printf("No patients registered yet.\n");
    }
    break;

                    case 5:
                        // Delete doctor
                        printf("\nEnter the doctor number you want to delete: ");
                        int doctorIndex;
                        scanf("%d", &doctorIndex);
                        if (doctorIndex > 0 && doctorIndex <= numDoctors) {
                            deleteDoctor(doctors, &numDoctors, doctorIndex - 1);
                            printf("Doctor deleted successfully.\n");
                        } else {
                            printf("Invalid doctor number.\n");
                        }
                        break;
                    case 6:
                        // Show patient prescriptions
                        showPrescriptions(patients, numPatients);
                        break;
                    case 7:
                        // Exit program
                        continueProgram = false;
                        printf("Exiting the program.\n");
                        break;
                    default:
                        printf("Invalid option.\n");
                        break;
                }
            } else {
                printf("Invalid security code. Access denied.\n");
            }

        } else if (strcmp(role, "exit") == 0) {
            continueProgram = false;
            printf("Exiting the program.\n");

        } else {
            printf("Invalid role. Please choose from 'doctor', 'patient', 'admin', or 'exit'.\n");
        }
    }

    return 0;
}

