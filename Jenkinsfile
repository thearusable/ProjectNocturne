pipeline {

    environment {
        registry = "thearusable/nocturne"
        registryCredential = 'dockerhub'
    }

    // no default agent - need to be specified per stage
    agent none

    stages {
        //@TODO - Prepare dockerfiles for other operating systems (Windows, Mac)
        stage('Docker'){
            agent any
            steps{
                script{
                    // build docker image from dockerfile
                    sh 'docker build -t ${registry} .'
                    // publish image on docker hub
                    if (env.BRANCH_NAME == "develop"){
                        docker.withRegistry( '', registryCredential ) {
                            sh 'docker push ${registry}:latest'
                        }
                    } else {
                        sh 'echo "Not a develop branch - SKIPPING."'
                    }
                }
            }
        }
        stage ('Static analysis') {
            agent any
            steps {
                //cppcheck
		        sh 'cppcheck --enable=all --inconclusive --verbose --xml --xml-version=2 . 2> cppcheck_report.xml'
                publishCppcheck pattern:'cppcheck_report.xml'
                //@TODO - add other tools
            }
        }
        
        stage ('Build engine'){
            agent { docker { image 'thearusable/nocturne:latest' } }
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    sh 'make all'
                }
            }
        }

        stage ('Testing'){
            agent { docker { image 'thearusable/nocturne:latest' } }
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    sh 'make test'
                    //@TODO - Generate coverage raport
                }
            } 
        }

        stage ('Documentation'){
            agent { docker { image 'thearusable/nocturne:latest' } }
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    sh 'make doc'
                    //@TODO - Publish doc files to GitHub
                }
            } 
        }
    }
    post {
        unsuccessful {
            emailext body: "${currentBuild.currentResult}: Job ${env.JOB_NAME} build ${env.BUILD_NUMBER}\n More info at: ${env.BUILD_URL}",
                recipientProviders: [[$class: 'DevelopersRecipientProvider'], [$class: 'RequesterRecipientProvider']],
                subject: "Jenkins Build ${currentBuild.currentResult}: Job ${env.JOB_NAME}"
        }
        fixed {
            emailext body: "${currentBuild.currentResult}: Job ${env.JOB_NAME} build ${env.BUILD_NUMBER}\n More info at: ${env.BUILD_URL}",
                recipientProviders: [[$class: 'DevelopersRecipientProvider'], [$class: 'RequesterRecipientProvider']],
                subject: "Jenkins Build ${currentBuild.currentResult}: Job ${env.JOB_NAME}"
        }
    }
}
