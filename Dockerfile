FROM busybox:latest
EXPOSE 8000
COPY ./faas-base64 /sbin/faas-base64
CMD [ "/sbin/faas-base64" ]